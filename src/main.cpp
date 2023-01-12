#include <Arduino.h>
#include <M5Core2.h>

void setup() {
    // Initialize the device so it is responsive
    M5.begin();

    // Do some initial stuff
    Serial.println("Hello from M5Stack Core2");
    M5.Lcd.setTextSize(3);
    M5.Lcd.fillScreen(OLIVE);
    M5.Lcd.setTextColor(WHITE);
    M5.Lcd.println("Hello World! Adam is the best");
}

void loop() {
    // Do some stuff repeatedly
    // Serial.println("Hello Again");
    // delay(1000);
}