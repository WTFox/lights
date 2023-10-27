#include "lullaby.h"

int lullabyFadeDirection = 1;   // 1 for increasing brightness, -1 for decreasing.

void lullabySetup(GlobalContext &context) {
    for (int i = 0; i < context.strip.numPixels(); i++) {
        context.strip.setPixelColor(i, 0, 0, LULLABY_MIN_BRIGHTNESS);  // A deep blue color to start.
    }
    context.strip.show();
}

void lullabyLoop(GlobalContext &context) {
    static int currentBrightness = LULLABY_MIN_BRIGHTNESS;  // Start at the minimum brightness.

    if (lullabyFadeDirection == 1) {
        currentBrightness += LULLABY_FADE_AMOUNT;
        if (currentBrightness >= LULLABY_MAX_BRIGHTNESS) {
            lullabyFadeDirection = -1;
        }
    } else if (lullabyFadeDirection == -1) {
        currentBrightness -= LULLABY_FADE_AMOUNT;
        if (currentBrightness <= LULLABY_MIN_BRIGHTNESS) {
            lullabyFadeDirection = 1;
        }
    }

    for (int i = 0; i < context.strip.numPixels(); i++) {
        context.strip.setPixelColor(i, 0, 0, currentBrightness);
    }

    context.strip.show();
    delay(30);  // Adjust this to slow down or speed up the breathing effect.
}
