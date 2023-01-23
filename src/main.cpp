#include <Arduino.h>
#include <M5Core2.h>


static int red = 0;
static int green = 0;
static int blue = 0;
static const int MAX_RED = 32;
static const int MAX_GREEN = 64;
static const int MAX_BLUE = 32;
int hexColor = 0x0000;
static unsigned long lastTS;

static void renderScreen();
static void drawSnowman(int screenWidth, int screenHeight, int snowmanBaseRadius, double ballShrinkFactor);

void setup()
{
    M5.begin();
    lastTS = millis();
    renderScreen();
}

void loop()
{
    M5.update();

    if (millis() >= lastTS + 50)
    {
        lastTS = millis();
        if (M5.BtnA.isPressed()) {
            red = (red == MAX_RED) ? 0 : red+1;
            renderScreen();
        }
        if (M5.BtnB.isPressed()) {
            green = (green == MAX_GREEN) ? 0 : green+1;
            renderScreen();
        }
        if (M5.BtnC.isPressed()) {
            blue = (blue == MAX_BLUE) ? 0 : blue+1;
            renderScreen();
        }
    }
}

static void renderScreen()
{
    Serial.printf("r=%d, g=%d, b=%d => ", red, green, blue);
    hexColor = red << 11 | green << 5 | blue;
    Serial.printf("0x%04X\n", hexColor);

    // Fill the screen with the specified color
    M5.Lcd.fillScreen(hexColor); 

    // Draw the snowman
    drawSnowman(M5.Lcd.width(), M5.Lcd.height(), M5.Lcd.width() / 6, 0.84);
}

static void drawSnowman(int screenWidth, int screenHeight, int snowmanBaseRadius, double ballShrinkFactor)
{

    int sWidth = screenWidth;
    int xScreenMid = sWidth / 2;
    int sHeight = screenHeight;
    Serial.printf("%d x %d res\n", sWidth, sHeight);


    int radius = snowmanBaseRadius;
    int diameter = radius * 2;
    int yOffset = 0;
    
    M5.Lcd.fillCircle(xScreenMid, sHeight - radius, radius, TFT_WHITE);


    int yBodyMid = 0;
    int yHeadMid = 0;

    for (int i = 0; i < 2; i++)
    {
        yOffset += diameter * ballShrinkFactor;
        radius *= ballShrinkFactor;
        diameter = radius * 2;
        int yCircleMid = sHeight - yOffset - radius;
        M5.Lcd.fillCircle(xScreenMid, yCircleMid, radius, TFT_WHITE);

        if (i == 0)
            yBodyMid = yCircleMid;
        else if (i == 1)
            yHeadMid = yCircleMid;
    }

    int rButton = 6;
    for (int i = -1; i < 2; i++)
        M5.Lcd.fillCircle(xScreenMid, yBodyMid + (rButton * 3 * i), rButton, TFT_BLACK);

    M5.Lcd.fillCircle(xScreenMid - 15, yHeadMid - 5, rButton, TFT_BLACK);
    M5.Lcd.fillCircle(xScreenMid + 15, yHeadMid - 5, rButton, TFT_BLACK);

    M5.Lcd.fillTriangle(xScreenMid, yHeadMid, xScreenMid, yHeadMid + 16, xScreenMid + 30, yHeadMid + 8, TFT_ORANGE);
}