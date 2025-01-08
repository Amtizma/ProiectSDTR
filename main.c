#include "DAVE.h"

#include "FREERTOS/semphr.h"

char buffer[50];  // Buffer pentru UART

SemaphoreHandle_t xSemaphore = NULL;
QueueHandle_t xQueue = NULL;

void set_servo_position(PWM_t *handle, uint8_t angle) {
    uint32_t duty_cycle;

    // Calculăm duty cycle-ul în funcție de unghi
    if (angle < 0) angle = 0;
    if (angle > 180) angle = 180;

   if (angle == 0) duty_cycle = 500;
   if(angle == 90) duty_cycle = 750;
   if(angle == 180) duty_cycle = 1000;

    // Setează duty cycle-ul pe canalul PWM utilizând funcția PWM_SetDutyCycle
    PWM_SetDutyCycle(handle, duty_cycle);

}


uint8_t calculate_servo_angle(uint32_t ldr1, uint32_t ldr2) {
	// Definim unghiurile de mișcare pe baza diferenței de lumină
	if (ldr1 > ldr2 + 200) { // Dacă fotorezistorul 1 detectează mai multă lumină, mișcăm servo spre dreapta
		return 180; // Servo la 180°
	} else if (ldr2 > ldr1 + 200) { // Dacă fotorezistorul 2 detectează mai multă lumină, mișcăm servo spre stânga
		return 0; // Servo la 0°
	} else {
		return 90; // Dacă luminile sunt aproape egale, punem servo la mijloc (90°)
	}
}

// Task-ul 1 - Citirea senzorilor și controlul servomotorului
void vTaskSensorProcessing(void *pvParameters) {
    static uint32_t result_termo1;
    static uint32_t result_termo2;
    static uint32_t result_voltage;

	ADC_MEASUREMENT_StartConversion(&ADC_MEASUREMENT_0);

    while (1) {
        result_termo1 = ADC_MEASUREMENT_GetResult(&ADC_MEASUREMENT_Termo_1_handle);
        result_termo2 = ADC_MEASUREMENT_GetResult(&ADC_MEASUREMENT_Termo_2_handle);
        result_voltage = ADC_MEASUREMENT_GetResult(&ADC_MEASUREMENT_Voltage_handle);

        // Calculăm unghiul pentru servomotor
        uint8_t angle = calculate_servo_angle(result_termo1, result_termo2);

        // Setăm poziția servomotorului
        set_servo_position(&PWM_0, angle);

        // Creăm un mesaj de transmis și îl punem în coadă
        sprintf(buffer, "LDR1: %lu, LDR2: %lu, Tensiune: %lu\n", result_termo1, result_termo2, result_voltage);
        xQueueSend(xQueue, (void *)buffer, portMAX_DELAY);

        // Sincronizăm cu Task-ul de transmitere
        vTaskDelay(5000); // Delay pentru a evita încărcarea excesivă a procesorului

		ADC_MEASUREMENT_StartConversion(&ADC_MEASUREMENT_0);

        xSemaphoreGive(xSemaphore);

    }
}


// Task-ul 2 - Comunicarea prin UART
void vTaskCommunication(void *pvParameters) {
    char buffer[50];

    while (1) {
        // Așteptăm ca Task-ul 1 să fi terminat procesarea
        xSemaphoreTake(xSemaphore, portMAX_DELAY);

        // Citim mesajul din coadă și îl transmitem prin UART
        if (xQueueReceive(xQueue, (void *)buffer, portMAX_DELAY)) {
            UART_Transmit(&UART_0, (uint8_t *)buffer, strlen(buffer));
        }
    }
}


int main(void) {
    DAVE_STATUS_t status;
    status = DAVE_Init(); /* Inițializarea aplicațiilor DAVE */

    if (status != DAVE_STATUS_SUCCESS) {
        while (1);
    }

    // Crearea semaforului
    xSemaphore = xSemaphoreCreateBinary();
    if (xSemaphore == NULL) {
        while (1);
    }

    // Crearea cozii de mesaje
    xQueue = xQueueCreate(10, sizeof(char[50]));
    if (xQueue == NULL) {
        while (1);
    }

    // Crearea task-urilor
    xTaskCreate(vTaskSensorProcessing, "SensorProcessing", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 1, NULL);
    xTaskCreate(vTaskCommunication, "Communication", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 1, NULL);

    // Pornește scheduler-ul RTOS
    vTaskStartScheduler();

    while (1);
}

