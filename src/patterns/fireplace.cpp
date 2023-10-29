#include "fireplace.h"

void fireplaceSetup(GlobalContext &context, PatternArgs &args) {
    for (int i = 0; i < NUM_LEDS; i++) {
        context.strip.setPixelColor(i, 0, 0, 0);
    }
}

void fireplaceLoop(GlobalContext &context, PatternArgs &args) {
    for (int i = 0; i < NUM_LEDS; i++) {
        int flicker = random(0, FIRE_INTENSITY);
        int r = 255 - flicker;
        int g = (90 - (flicker / 2));
        int b = 0;

        // Ensure no out-of-bounds RGB values
        r = constrain(r, 0, 255);
        g = constrain(g, 0, 255);

        context.strip.setPixelColor(i, g, r, b);
    }
    context.strip.show();
    delay(50); // Short delay for visual effect
}
