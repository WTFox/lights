#include "rainbowConfetti.h"

int confettiColorChange[100] = {
    0}; // Adjust array size to match your strip's LED count

uint32_t Wheel(GlobalContext &context, byte WheelPos) {
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
    delay(50); // Adjust for your desired speed
}
