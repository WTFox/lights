#include "night_sky.h"

int nightSkyBrightness[100] = {
    0}; // Adjust array size if your strip has more or less LEDs
int nightSkyFadeDirection[100] = {0};

void nightSkySetup(GlobalContext &context, PatternArgs &args) {
    for (int i = 0; i < context.strip.numPixels(); i++) {
        context.strip.setPixelColor(
            i, 0, 0, NIGHTSKY_MIN_BRIGHTNESS); // Soft ambient blue
        nightSkyBrightness[i] = NIGHTSKY_MIN_BRIGHTNESS;
        nightSkyFadeDirection[i] = 0;
    }
    context.strip.show();
}

void nightSkyLoop(GlobalContext &context, PatternArgs &args) {
    for (int i = 0; i < context.strip.numPixels(); i++) {
        if (random(100) < NIGHTSKY_STAR_CHANCE &&
            nightSkyFadeDirection[i] == 0) {
            nightSkyFadeDirection[i] = 1; // This star will start to twinkle
        }

        if (nightSkyFadeDirection[i] == 1) {
            nightSkyBrightness[i] += random(1, NIGHTSKY_FADE_AMOUNT + 1);
            if (nightSkyBrightness[i] >= NIGHTSKY_MAX_BRIGHTNESS) {
                nightSkyFadeDirection[i] = -1;
            }
        } else if (nightSkyFadeDirection[i] == -1) {
            nightSkyBrightness[i] -= random(1, NIGHTSKY_FADE_AMOUNT + 1);
            if (nightSkyBrightness[i] <= NIGHTSKY_MIN_BRIGHTNESS) {
                nightSkyFadeDirection[i] = 0;
            }
        }

        context.strip.setPixelColor(i, 0, 0, nightSkyBrightness[i]);
    }

    context.strip.show();
    delay(50); // Adjust to slow down or speed up the twinkling effect.
}
