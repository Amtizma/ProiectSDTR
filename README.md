# Light Tracking System for Solar Panel Optimization

This project presents the design and implementation of a light tracking system aimed at optimizing the positioning of solar panels for improved energy capture. The system utilizes two light-dependent resistors (LDRs) to detect light intensity from different directions, enabling the precise tracking of the sun’s position. A servo motor is controlled via a Pulse-Width Modulation (PWM) signal to adjust the solar panel’s orientation in real time.

## Key Features

- **Light Detection**: Two LDRs detect light intensity from different directions.
- **Real-Time Adjustment**: A servo motor adjusts the solar panel orientation using PWM control.
- **Microcontroller**: The system is powered by the Infineon XMC 4700 Relax Kit Lite microcontroller.
- **Multitasking**: FreeRTOS is used to manage the multitasking environment for efficient operation.

## System Components

- **Microcontroller**: Infineon XMC 4700 Relax Kit Lite
- **Sensors**: Two Light-Dependent Resistors (LDRs)
- **Actuator**: Servo motor controlled by PWM
- **Operating System**: FreeRTOS for task management

## Performance Evaluation

The system was evaluated through a series of performance tests, comparing the energy output of a dynamically adjusted solar panel with a static panel under various lighting conditions. The results demonstrate significant improvements in energy efficiency, with voltage outputs showing up to an 80% increase compared to a static configuration.

## Results

- **Energy Efficiency**: Up to 80% increase in voltage output compared to a static solar panel.
- **Real-Time Tracking**: Continuous adjustment to optimize solar panel orientation.

## Conclusion

The light tracking system provides a practical and efficient solution for enhancing solar panel energy capture by dynamically adjusting to the sun's position. This project demonstrates the potential of integrating microcontroller-based control with real-time operating systems for renewable energy applications.

