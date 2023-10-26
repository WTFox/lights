#include "twinkle.h"

int ledBrightness[NUM_LEDS] = {0};
int fadeDirection[NUM_LEDS] = {0};
int currentlyTwinkling = 0;

void twinkleSetup(GlobalContext &context) {
    for (int i = 0; i < NUM_LEDS; i++) {
        context.strip.setPixelColor(i, 0, 0, 25);
    }
}

void twinkleLoop(GlobalContext &context) {
    if (currentlyTwinkling < MAX_TWINKLING && random(100) < TWINKLE_CHANCE) {

        int randLed = random(NUM_LEDS);
        if (fadeDirection[randLed] == 0) {
            fadeDirection[randLed] = 1;
            currentlyTwinkling++;
        }
    }

    for (int i = 0; i < NUM_LEDS; i++) {
        if (fadeDirection[i] == 1) {
            ledBrightness[i] += FADE_AMOUNT;
            if (ledBrightness[i] >= MAX_BRIGHTNESS) {
                fadeDirection[i] = -1;
            }
        } else if (fadeDirection[i] == -1) {
            ledBrightness[i] -= FADE_AMOUNT;
            if (ledBrightness[i] <= 0) {
                fadeDirection[i] = 0;
                ledBrightness[i] = 0;
                currentlyTwinkling--;
            }
        }

        if (fadeDirection[i] != 0) {
            context.strip.setPixelColor(i, ledBrightness[i], ledBrightness[i],
                                        ledBrightness[i] /
                                            2); // A white or yellowish star
        } else {
            context.strip.setPixelColor(i, 0, 0, 25); // Dark blue background
        }
    }
    context.strip.show();
}
