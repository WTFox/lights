#include "confetti.h"

int confettiBrightness[NUM_LEDS] = {0};
int confettiFadeDirection[NUM_LEDS] = {0};

void confettiSetup(GlobalContext &context, PatternArgs &args) {
    for (int i = 0; i < context.strip.numPixels(); i++) {
        context.strip.setPixelColor(i, 0, 0, 0); // Start with all LEDs off
    }
    context.strip.show();
}

void confettiLoop(GlobalContext &context, PatternArgs &args) {
    static unsigned long lastUpdate = 0; // Stores the last update timestamp
    if (millis() - lastUpdate < CONFETTI_UPDATE_INTERVAL) {
        return; // If it hasn't been long enough, just return without updating
    }
    lastUpdate = millis(); // Update the last update timestamp

    for (int i = 0; i < context.strip.numPixels(); i++) {
        if (random(100) < CONFETTI_CHANCE && confettiFadeDirection[i] == 0) {
            // Randomly determine the color of the speckle
            byte r = random(256);
            byte g = random(256);
            byte b = random(256);
            confettiFadeDirection[i] = 1; // Set direction to "increasing"
            context.strip.setPixelColor(i, g, r, b);
        }

        if (confettiFadeDirection[i] == 1) {
            confettiBrightness[i] += CONFETTI_FADE_AMOUNT;
            if (confettiBrightness[i] >= 255) {
                confettiFadeDirection[i] =
                    -1; // Change direction to "decreasing"
            }
        } else if (confettiFadeDirection[i] == -1) {
            confettiBrightness[i] -= CONFETTI_FADE_AMOUNT;
            if (confettiBrightness[i] <= 0) {
                confettiFadeDirection[i] =
                    0; // Reset and wait for the next speckle
                context.strip.setPixelColor(i, 0, 0, 0); // Turn off the LED
            }
        }
    }
    context.strip.show();
}
