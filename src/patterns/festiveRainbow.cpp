#include "festiveRainbow.h"

#define DELAY_TIME 20 // Speed of the rainbow cycle

void festiveRainbowSetup(GlobalContext &context) {
    context.strip.begin();
    context.strip.show(); // Initialize all pixels to 'off'
}

void festiveRainbowLoop(GlobalContext &context) {
    uint16_t i, j;

    for (j = 0; j < 256; j++) {
        for (i = 0; i < NUM_LEDS; i++) {
            context.strip.setPixelColor(
                i, festiveWheel((i + j) & 255, context.strip));
        }
        context.strip.show();
        delay(DELAY_TIME);
    }
}

uint32_t festiveWheel(byte WheelPos, Adafruit_NeoPixel &strip) {
    WheelPos = 255 - WheelPos;
    if (WheelPos < 85) {
        return strip.Color(255 - WheelPos * 3, WheelPos * 2,
                           0); // Red to yellow gradient
    }
    if (WheelPos < 170) {
        WheelPos -= 85;
        return strip.Color(0, WheelPos * 3, 0); // Green shades
    }
    WheelPos -= 170;
    return strip.Color(WheelPos * 3, 255 - WheelPos * 2,
                       WheelPos * 2); // Yellow to red gradient
}
