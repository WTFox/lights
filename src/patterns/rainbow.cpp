#include "rainbow.h"

void rainbowSetup(GlobalContext &context) {}

void rainbowLoop(GlobalContext &context) {
    uint16_t i;

    for (i = 0; i < context.strip.numPixels(); i++) {
        context.strip.setPixelColor(
            i, Wheel((i + context.iteration) & 255, context));
    }

    context.strip.show();
    delay(20);
}

uint32_t Wheel(byte WheelPos, GlobalContext &context) {
    WheelPos = 255 - WheelPos;
    if (WheelPos < 85) {
        uint8_t r = 255 - WheelPos * 3;
        uint8_t g = 0;
        uint8_t b = WheelPos * 3;
        return context.strip.Color(g, r, b);
    }
    if (WheelPos < 170) {
        WheelPos -= 85;
        uint8_t r = 0;
        uint8_t g = WheelPos * 3;
        uint8_t b = 255 - WheelPos * 3;
        return context.strip.Color(0, g, r, b);
    }
    WheelPos -= 170;
    uint8_t r = WheelPos * 3;
    uint8_t g = 255 - WheelPos * 3;
    uint8_t b = 0;
    return context.strip.Color(g, r, b);
}
