#include "halloween.h"

void halloweenSetup(GlobalContext &context) {}

void halloweenLoop(GlobalContext &context) {
    for (int i = 0; i < context.strip.numPixels(); i++) {
        uint8_t r = 255;
        uint8_t g = 50;
        uint8_t b = 0;
        context.strip.setPixelColor(i, context.strip.Color(g, r, b));
    }

    if (randomInt() < HALLOWEEN_GLIMMER_CHANCE) {
        uint8_t r = 0;
        uint8_t g = 255;
        uint8_t b = 0;
        context.strip.setPixelColor(random16(NUM_LEDS), g, r, b);
    }

    context.strip.show();
    delay(100);
}
