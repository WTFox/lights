#include "twinkle.h"

int ledBrightness[NUM_LEDS] = {0};
int fadeDirection[NUM_LEDS] = {0};
int currentlyTwinkling = 0;

void twinkleSetup(GlobalContext &context) {
    for (int i = 0; i < NUM_LEDS; i++) {
        uint8_t r = 0;
        uint8_t g = 0;
        uint8_t b = 25;
        context.strip.setPixelColor(i, g, r, b);
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
            uint8_t r = ledBrightness[i];
            uint8_t g = ledBrightness[i];
            uint8_t b = ledBrightness[i] / 2;
            context.strip.setPixelColor(i, g, r,
                                        b); // A white or yellowish star
        } else {
            uint8_t r = 0;
            uint8_t g = 0;
            uint8_t b = 25;

            context.strip.setPixelColor(i, g, r, b); // Dark blue background
        }
    }
    context.strip.show();
}
