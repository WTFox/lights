#include "rainbow.h"

void rainbowSetup(GlobalContext &context, PatternArgs &args) {}

void rainbowLoop(GlobalContext &context, PatternArgs &args) {
    uint16_t i, j;

    for (j = 0; j < 256; j++) {
        for (i = 0; i < context.strip.numPixels(); i++) {
            context.strip.setPixelColor(
                i, Wheel(((i * 256 / NUM_LEDS) + j) & 255, context));
        }

        if (random(100) < args.chance_of_sparkle) {
            context.strip.setPixelColor(random(0, NUM_LEDS), 255, 255, 255);
        }

        context.strip.show();
        delay(20);
    }
}

uint32_t Wheel(byte WheelPos, GlobalContext &context) {
    WheelPos = 255 - WheelPos;
    if (WheelPos < 85) {
        uint8_t r = 255 - WheelPos * 3;
        uint8_t g = 0;
        uint8_t b = WheelPos * 3;
        return context.strip.Color(r, g, b);
    }
    if (WheelPos < 170) {
        WheelPos -= 85;
        uint8_t r = 0;
        uint8_t g = WheelPos * 3;
        uint8_t b = 255 - WheelPos * 3;
        return context.strip.Color(r, g, b);
    }
    WheelPos -= 170;
    uint8_t r = WheelPos * 3;
    uint8_t g = 255 - WheelPos * 3;
    uint8_t b = 0;
    return context.strip.Color(r, g, b);
}
