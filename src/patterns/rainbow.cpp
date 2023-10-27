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
        return context.strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
    }
    if (WheelPos < 170) {
        WheelPos -= 85;
        return context.strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
    }
    WheelPos -= 170;
    return context.strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}
