#include "colored_sparkle_fade.h"

int beadBrightness[NUM_LEDS] = {0};
int fadeDirection[NUM_LEDS] = {0};

void coloredSparkleFadeSetup(GlobalContext &context, PatternArgs &args) {
    Color color = Color(args.primary_color);
    for (int i = 0; i < context.strip.numPixels(); i++) {
        context.strip.setPixelColor(i, color.g, color.r, color.b);
    }
    context.strip.show();
}

void coloredSparkleFadeLoop(GlobalContext &context, PatternArgs &args) {
    Color primaryColor = Color(args.primary_color);
    Color secondaryColor = Color(args.sparkle_color);

    for (int i = 0; i < context.strip.numPixels(); i++) {
        if (fadeDirection[i] == 0 && random(100) < args.chance_of_sparkle) {
            fadeDirection[i] = 1;
        }

        if (fadeDirection[i] == 1) {
            beadBrightness[i] += FADE_AMOUNT;
            if (beadBrightness[i] >= 255) {
                fadeDirection[i] = -1;
            }
        } else if (fadeDirection[i] == -1) {
            beadBrightness[i] -= FADE_AMOUNT;
            if (beadBrightness[i] <= 0) {
                fadeDirection[i] = 0;
                beadBrightness[i] = 0;
            }
        }

        uint8_t interpR = (primaryColor.r * (255 - beadBrightness[i]) +
                           secondaryColor.r * beadBrightness[i]) /
                          255;
        uint8_t interpG = (primaryColor.g * (255 - beadBrightness[i]) +
                           secondaryColor.g * beadBrightness[i]) /
                          255;
        uint8_t interpB = (primaryColor.b * (255 - beadBrightness[i]) +
                           secondaryColor.b * beadBrightness[i]) /
                          255;

        context.strip.setPixelColor(i, interpG, interpR, interpB);
    }
    context.strip.show();
    delay(50);
}
