#include "rainbowConfetti.h"

// Adjust array size to match your strip's LED count
int confettiColorChange[100] = {0};

uint32_t Wheel(GlobalContext &context, byte WheelPos) {
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

void rainbowConfettiSetup(GlobalContext &context) {
    for (int i = 0; i < context.strip.numPixels(); i++) {
        context.strip.setPixelColor(
            i, Wheel(context, (i * 256 / context.strip.numPixels()) & 255));
    }
    context.strip.show();
}

void rainbowConfettiLoop(GlobalContext &context) {
    for (int i = 0; i < context.strip.numPixels(); i++) {
        if (random(100) < RAINBOW_CONFETTI_CHANCE) {
            confettiColorChange[i] =
                (confettiColorChange[i] + random(5, 20)) % 256;
            context.strip.setPixelColor(i,
                                        Wheel(context, confettiColorChange[i]));
        } else {
            context.strip.setPixelColor(
                i, Wheel(context, (i * 256 / context.strip.numPixels() +
                                   confettiColorChange[i]) &
                                      255));
        }
    }
    context.strip.show();
}
