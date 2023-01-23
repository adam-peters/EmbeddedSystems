#include <Arduino.h>
#include <M5Core2.h>

//    GOAL: 
//    MODE 1: GREEN=>YELLOW=>RED=>GREEN... (every 1s)
//    MODE 2: RED=>BLACK=>RED (every 1s)
//    BTN_A toggles between modes 1 and 2; init to mode 1

enum State { S_GREEN, S_YELLOW, S_RED, S_BLACK };
enum Mode { M_NORMAL, M_EMERGENCY };

static unsigned long lastTS;
static State state = S_GREEN;
static Mode mode = M_NORMAL;

void setup() {
    M5.begin();
}

void loop() {

    M5.update();
    if(M5.BtnA.wasPressed()) {
        if (mode == M_NORMAL) {
            mode = M_EMERGENCY;
            state = S_RED;
        } else {
            mode = M_NORMAL;
            state = S_GREEN;
        }
    }

    if(millis() >= lastTS + 1000) {
        lastTS = millis();
        
        if(mode == M_NORMAL) {
            if(state == S_GREEN)
                state = S_YELLOW;
            else if (state == S_YELLOW)
                state = S_RED;
            else
                state = S_GREEN;  
        } else {
            if(state == S_RED)
                state = S_BLACK;
            else 
                state = S_RED;
        }
    }

    if(state == S_GREEN)
        M5.Lcd.fillScreen(TFT_GREEN);
    else if (state == S_YELLOW)
        M5.Lcd.fillScreen(TFT_YELLOW);
    else if (state == S_RED)
        M5.Lcd.fillScreen(TFT_RED);
    else if (state == S_BLACK)
        M5.Lcd.fillScreen(TFT_BLACK);
}