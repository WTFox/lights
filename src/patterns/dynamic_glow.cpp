#include "dynamic_glow.h"

void dynamicGlowSetup(GlobalContext &context, PatternArgs &args) {
    for (int i = 0; i < NUM_LEDS; i++) {
        context.strip.setPixelColor(i, 0, 0, 0);
    }
}

void dynamicGlowLoop(GlobalContext &context, PatternArgs &args) {
    Color primaryColor = Color(args.primary_color);

    for (int i = 0; i < NUM_LEDS; i++) {
        int flicker = random(0, args.intensity);

        int r = primaryColor.r - flicker;
        int g = primaryColor.g - (flicker / 2);
        int b = primaryColor.b -
                (flicker / 3); // If you want blue to have a different effect

        // Ensure no out-of-bounds RGB values
        r = constrain(r, 0, 255);
        g = constrain(g, 0, 255);
        b = constrain(b, 0, 255);

        context.strip.setPixelColor(i, g, r, b);
    }
    context.strip.show();
    delay(50); // Short delay for visual effect
}
