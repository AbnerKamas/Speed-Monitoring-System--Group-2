const int sensor1_pin = 7;  // Entrance sensor
const int sensor2_pin = 8;  // Exit sensor
const int reset_pin =  2;   // Reset button
const int overspeed_pin = 13; // Output pin for overspeed alert
const int safespeed_pin = 12; // Output pin for safespeed limit 
const float distance_m = 100.0;  // Distance between sensors in meters
const float time_correction_factor = 1;  // Adjust for Tinkercad's faster millis()


unsigned long time1 = 0;
unsigned long time2 = 0;
bool sensor1_triggered = false;
bool sensor2_triggered = false;

void setup() {
    Serial.begin(9600);
    pinMode(sensor1_pin, INPUT_PULLUP);
    pinMode(sensor2_pin, INPUT_PULLUP);
    pinMode(reset_pin, INPUT_PULLUP);
    pinMode(overspeed_pin, OUTPUT);
    pinMode(safespeed_pin, OUTPUT);
    
    Serial.println("Vehicle Speed Monitoring System Ready");
}

void loop() {
    // Check if Reset Button is Pressed
    if (digitalRead(reset_pin) == LOW) { 
        delay(200);
        resetSystem();
    }

    if (digitalRead(sensor1_pin) == HIGH && !sensor1_triggered) {
        delay(50); // Debounce
        if (digitalRead(sensor1_pin) == HIGH) { // Confirm button press
            digitalWrite(overspeed_pin, LOW);  // Reset overspeed alert
            time1 = millis();
            sensor1_triggered = true;
            Serial.println("Vehicle Entry Detected - Timer Started");
        }
    }

    if (digitalRead(sensor2_pin) == HIGH && sensor1_triggered && !sensor2_triggered) {
        delay(50); // Debounce
        if (digitalRead(sensor2_pin) == HIGH) { // Confirm button press
            time2 = millis();
            sensor2_triggered = true;
            Serial.println("Vehicle Exit Detected - Timer Stopped");

            // Calculate time difference and apply correction
            float time_sec = ((time2 - time1) / 1000.0) * time_correction_factor;
            float speed_kmh = (distance_m / time_sec) * 3.6;

            // Display time and speed
            Serial.print("Time Elapsed: ");
            Serial.print(time_sec, 3);
            Serial.println(" seconds");

            Serial.print("Estimated Vehicle Speed: ");
            Serial.print(speed_kmh, 2);
            Serial.println(" km/h");

            // Check for overspeed
            if (speed_kmh > 60.0) {  
                Serial.println("Overspeed Detected");
                digitalWrite(overspeed_pin, HIGH);  // Activate alert
            }
          if (speed_kmh < 60.1) {  
                Serial.println("Speed is within range");
                digitalWrite(safespeed_pin, HIGH);  // Activate GREEN LED
            }

            // Reset for next vehicle
            sensor1_triggered = false;
            sensor2_triggered = false;
        }
    }
}

// Function to Reset System
void resetSystem() {
    time1 = 0;
    time2 = 0;
    sensor1_triggered = false;
    sensor2_triggered = false;
    digitalWrite(overspeed_pin, LOW);  // Turn off overspeed alert
    digitalWrite(safespeed_pin, LOW);// Turn off LED

    Serial.println("System Reset - Ready for new measurement");
}