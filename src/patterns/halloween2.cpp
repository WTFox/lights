#include "halloween2.h"

int halloween2BeadBrightness[100] = {
    0}; // Assuming a strip size of 100, adjust if different.
int halloween2FadeDirection[100] = {0}; // Direction for each bead.

void halloween2Setup(GlobalContext &context, PatternArgs &args) {
    for (int i = 0; i < context.strip.numPixels(); i++) {
        uint8_t r = 255;
        uint8_t g = 50;
        uint8_t b = 0;
        context.strip.setPixelColor(i, g, r, b); // Set all LEDs to orange.
    }
    context.strip.show();
}

void halloween2Loop(GlobalContext &context, PatternArgs &args) {
    for (int i = 0; i < context.strip.numPixels(); i++) {
        if (halloween2FadeDirection[i] == 0 &&
            random(100) < HALLOWEEN_2_GREEN_BEAD_CHANCE) {
            halloween2FadeDirection[i] = 1;
        }

        if (halloween2FadeDirection[i] == 1) {
            halloween2BeadBrightness[i] += HALLOWEEN_2_FADE_AMOUNT;
            if (halloween2BeadBrightness[i] >=
                HALLOWEEN_2_MAX_GREEN_BRIGHTNESS) {
                halloween2FadeDirection[i] = -1;
            }
        } else if (halloween2FadeDirection[i] == -1) {
            halloween2BeadBrightness[i] -= HALLOWEEN_2_FADE_AMOUNT;
            if (halloween2BeadBrightness[i] <= 0) {
                halloween2FadeDirection[i] = 0;
                halloween2BeadBrightness[i] = 0;
            }
        }

        if (halloween2FadeDirection[i] != 0) {
            context.strip.setPixelColor(i, halloween2BeadBrightness[i], 0,
                                        0); // Green color.
        } else {
            uint8_t r = 255;
            uint8_t g = 50;
            uint8_t b = 0;

            context.strip.setPixelColor(i, g, r, b); // Orange color.
        }
    }
    context.strip.show();
    delay(50); // Slow down the loop for smoother transitions.
}
