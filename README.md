This project presents the design and implementation
of a light tracking system aimed at optimizing the positioning of
solar panels for improved energy capture. The system utilizes
two light-dependent resistors (LDRs) to detect light intensity
from different directions, enabling the precise tracking of the
sun’s position. A servo motor is controlled via a Pulse-Width
Modulation (PWM) signal to adjust the solar panel’s orientation
in real time. The core of the system is based on the Infineon
XMC 4700 Relax Kit Lite microcontroller, which processes
sensor data and drives the motor, with FreeRTOS managing
the multitasking environment for efficient operation. The system
was evaluated through a series of performance tests, comparing
the energy output of a dynamically adjusted solar panel with
a static panel under various lighting conditions. The results
demonstrate significant improvements in energy efficiency, with
voltage outputs showing up to an 80% increase compared to
a static configuration.
