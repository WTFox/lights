#include "twinkle.h"

#define SOFT_WHITE_LEVEL 30
#define MAX_BRIGHTNESS 255
#define MIN_BRIGHTNESS SOFT_WHITE_LEVEL

static uint8_t ledState[NUM_LEDS]; // To keep track if LED is ON or OFF
static int8_t brightnessDirection[NUM_LEDS]; // Direction to adjust brightness: 1 for
                                   // increasing, -1 for decreasing
static uint8_t targetBrightness[NUM_LEDS]; // Target brightness when LED is ON

void twinkleSetup(GlobalContext &context) {
    for (int i = 0; i < context.strip.numPixels(); i++) {
        ledState[i] = random(2); // Randomly set initial state
        brightnessDirection[i] = 1;
        targetBrightness[i] = random(SOFT_WHITE_LEVEL, MAX_BRIGHTNESS);
        context.strip.setPixelColor(
            i,
            context.strip.Color(0, 0, SOFT_WHITE_LEVEL)); // Initial soft white
    }
    context.strip.show();
}

void twinkleLoop(GlobalContext &context) {
    for (int i = 0; i < context.strip.numPixels(); i++) {
        uint32_t currentColor = context.strip.getPixelColor(i);
        uint8_t currentBrightness =
            currentColor & 0xFF; // Extract the blue channel for brightness

        if (ledState[i] == 1) { // If LED is twinkling
            currentBrightness += brightnessDirection[i];

            if (currentBrightness >= targetBrightness[i]) {
                brightnessDirection[i] = -1; // Start dimming
            } else if (currentBrightness <= SOFT_WHITE_LEVEL) {
                brightnessDirection[i] = 1; // Start brightening
                targetBrightness[i] =
                    random(SOFT_WHITE_LEVEL,
                           MAX_BRIGHTNESS); // Get new target brightness
            }

            context.strip.setPixelColor(
                i, context.strip.Color(0, 0, currentBrightness));
        } else if (random(100) < 2) { // 2% chance to start twinkling
            ledState[i] = 1;
            targetBrightness[i] = random(SOFT_WHITE_LEVEL, MAX_BRIGHTNESS);
        }
    }

    context.strip.show();
    delay(20); // You can adjust this for faster/slower twinkling
}
