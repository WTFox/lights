#include "christmas_rainbow.h"

#define DELAY_TIME 20 // Speed of the rainbow cycle

void christmasRainbowSetup(GlobalContext &context, PatternArgs &args) {
    context.strip.begin();
    context.strip.show(); // Initialize all pixels to 'off'
}

void christmasRainbowLoop(GlobalContext &context, PatternArgs &args) {
    uint16_t i, j;

    for (j = 0; j < 256; j++) {
        for (i = 0; i < context.strip.numPixels(); i++) {
            context.strip.setPixelColor(
                i, festiveWheel(((i * 256 / NUM_LEDS) + j) & 255, context));
        }
        if (random(100) < args.chance_of_sparkle) {
            context.strip.setPixelColor(random(0, NUM_LEDS), 255, 255, 255);
        }
        context.strip.show();
        delay(DELAY_TIME);
    }
}

uint32_t festiveWheel(byte WheelPos, GlobalContext &context) {
    WheelPos = 255 - WheelPos;
    if (WheelPos < 85) {
        uint8_t r = 255 - WheelPos * 3;
        uint8_t g = WheelPos * 2;
        uint8_t b = 0;
        return context.strip.Color(g, r, b);
    }
    if (WheelPos < 170) {
        WheelPos -= 85;
        uint8_t r = 0;
        uint8_t g = WheelPos * 3;
        uint8_t b = 0;
        return context.strip.Color(g, r, b); // Green shades
    }
    WheelPos -= 170;
    uint8_t r = WheelPos * 3;
    uint8_t g = 255 - WheelPos * 2;
    uint8_t b = WheelPos * 2;
    return context.strip.Color(g, r, b); // Yellow to red gradient
}
