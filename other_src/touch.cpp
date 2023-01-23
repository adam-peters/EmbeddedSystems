#include <Arduino.h>
#include <M5Core2.h>

static bool ledIsOn = false;
static unsigned long secondsOn = 0;
static unsigned long buttonAPresses = 0;
static unsigned long lastTS;
static HotZone hz(0, 0, 320, 240);

void setup() {
    // Initialize the device so it is responsive
    M5.begin();

    // Do some initial stuff
    Serial.println("Hello from M5Stack Core2");
    M5.Lcd.setTextSize(3);
    M5.Lcd.fillScreen(OLIVE);
    M5.Lcd.setTextColor(WHITE);
    M5.Lcd.println("Hello World! Adam is the best");
    M5.Axp.SetLed(ledIsOn);

    lastTS = millis();
}

void loop() {

    M5.update();

    // Check for button input
    if(M5.BtnA.wasPressed()) {
        Serial.printf("\tYou pressed button A %lu times.\n", buttonAPresses);
        buttonAPresses++;
    }

    // Check for touch input
    if (M5.Touch.ispressed()) {
        TouchPoint tp = M5.Touch.getPressPoint();
        if(hz.inHotZone(tp)) {
            Serial.printf("\tYou pressed touch screen @ (%d, %d)\n", tp.x, tp.y);
        } 
    }

    // Do stuff repeatedly each second
    if(millis() >= lastTS + 1000) {
        lastTS = millis();
        Serial.printf("Hello again (%lu secs)!\n", secondsOn);
        ledIsOn = !ledIsOn;
        M5.Axp.SetLed(ledIsOn);
    }
}