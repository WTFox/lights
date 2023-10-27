#include "halloween.h"

void halloweenSetup(GlobalContext &context) {}

void halloweenLoop(GlobalContext &context) {
    for (int i = 0; i < context.strip.numPixels(); i++) {
        context.strip.setPixelColor(i, context.strip.Color(255, 50, 0));
    }

    if (randomInt() < HALLOWEEN_GLIMMER_CHANCE) {
        context.strip.setPixelColor(random16(NUM_LEDS), 0, 255, 0);
    }

    context.strip.show();
    delay(100);
}
