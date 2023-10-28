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
        uint8_t r = 255 - WheelPos * 3;
        uint8_t g = WheelPos * 2;
        uint8_t b = 0;
        return strip.Color(g, r, b);
    }
    if (WheelPos < 170) {
        WheelPos -= 85;
        uint8_t r = 0;
        uint8_t g = WheelPos * 3;
        uint8_t b = 0;
        return strip.Color(g, r, b); // Green shades
    }
    WheelPos -= 170;
    uint8_t r = WheelPos * 3;
    uint8_t g = 255 - WheelPos * 2;
    uint8_t b = WheelPos * 2;
    return strip.Color(g, r, b); // Yellow to red gradient
}
