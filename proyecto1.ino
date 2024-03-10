#include "Led.h"
#include "UltrasonicSensor.h"
#include <chrono>

Led redLed(18);
Led yellowLed(19);
Led greenLed(21);
UltrasonicSensor sensor(2, 15);

void setup() {
    Serial.begin(9600);
}

void loop() {
    auto start_time = std::chrono::high_resolution_clock::now();
    float distanceMeasured = sensor.returnDistancInCentimeters();
    Serial.print(distanceMeasured);
    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);

    if (distanceMeasured > 400) {
        Serial.println(" OUT OF RANGE");
        return;
    }
   
    Serial.println("cm");
    delay(100);
    Serial.print("Delay time ");
    Serial.print(duration.count());
    Serial.println(" milliseconds");
    delay(100);
    
    
    if (distanceMeasured > 132 && distanceMeasured <= 266) {
        yellowLed.turnOn();
    } else {
        yellowLed.turnOff();
    }

    if (distanceMeasured >= 2 && distanceMeasured <= 132) {
        redLed.blinkWithFrequency(0.5);
    }

    if (distanceMeasured > 266 && distanceMeasured <= 400) {
        redLed.blinkWithFrequency(0.1);
        yellowLed.blinkWithFrequency(0.1);
        greenLed.blinkWithFrequency(0.1);
    }
}
