#include "rainbow_confetti.h"

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

void rainbowConfettiSetup(GlobalContext &context, PatternArgs &args) {
    for (int i = 0; i < context.strip.numPixels(); i++) {
        context.strip.setPixelColor(
            i, Wheel(context, (i * 256 / context.strip.numPixels()) & 255));
    }
    context.strip.show();
}

void rainbowConfettiLoop(GlobalContext &context, PatternArgs &args) {
    static unsigned long lastConfettiUpdate = 0;
    const unsigned long confettiUpdateInterval = 50; // adjust as needed

    for (int i = 0; i < context.strip.numPixels(); i++) {
        // Always set the regular rainbow pattern
        context.strip.setPixelColor(
            i, Wheel(context, (i * 256 / context.strip.numPixels()) & 255));
    }

    // Check if it's time to update the confetti
    if (millis() - lastConfettiUpdate > confettiUpdateInterval) {
        for (int i = 0; i < context.strip.numPixels(); i++) {
            if (random(100) < RAINBOW_CONFETTI_CHANCE) {
                confettiColorChange[i] =
                    (confettiColorChange[i] + random(5, 20)) % 256;
                context.strip.setPixelColor(
                    i, Wheel(context, confettiColorChange[i]));
            }
        }
        lastConfettiUpdate = millis();
    }

    context.strip.show();
}
