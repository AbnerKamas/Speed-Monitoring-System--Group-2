# Speed-Monitoring-System-Group-2
A vehicle speed monitoring system using Arduino Uno R3 and PIR sensors to detect over-speeding and safe driving by calculating vehicle speed based on sensor triggers.


In this project, two PIR sensors are mounted 100 meters apart—one at the entry point and the other at the exit point of a road segment. When a vehicle enters, the infrared radiation emitted by its engine and tires (due to heat and friction) is detected by the first PIR sensor, which then sends a logic HIGH signal to the Arduino Uno R3, starting a timer.

As the vehicle passes the second PIR sensor at the exit point, it also detects the infrared signature and sends another logic HIGH signal to the Arduino, which then stops the timer. Using the known distance (100 meters) and the time elapsed, the Arduino calculates the vehicle’s speed.
	•	If the vehicle is over-speeding, a piezoelectric buzzer is triggered as a warning.
	•	If the vehicle is within the safe speed limit, the system can be manually reset by the operator using a push-button.

This setup provides a simple but effective way to monitor and manage vehicle speed using infrared technology and basic microcontroller logic.
Below is a Youtube Video explaining everything 
https://youtu.be/Cb3RFh_t8DA?si=96IMQGKs8imvht6b

