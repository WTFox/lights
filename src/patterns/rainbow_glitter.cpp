#include "rainbow_glitter.h"

// TODO: move this to PatternArgs
#define chanceOfGlitter 10

void rainbowWithGlitterSetup(GlobalContext &context, PatternArgs &args) {}

void rainbowWithGlitterLoop(GlobalContext &context, PatternArgs &args) {
    uint16_t i, j;

    for (j = 0; j < 256; j++) { // 1 cycle of all colors on wheel
        for (i = 0; i < context.strip.numPixels(); i++) {
            context.strip.setPixelColor(
                i, Wheel(((i * 256 / context.strip.numPixels()) + j) & 255,
                         context));
        }

        if (randomInt() < chanceOfGlitter) {
            context.strip.setPixelColor(random16(NUM_LEDS), 255, 255, 255);
        }

        context.strip.show();
        delay(20);
    }
}
