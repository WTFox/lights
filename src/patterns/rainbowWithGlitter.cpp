#include "rainbowWithGlitter.h"

void rainbowWithGlitterSetup(GlobalContext &context) {}

void rainbowWithGlitterLoop(GlobalContext &context) {
    uint16_t i;

    for (i = 0; i < context.strip.numPixels(); i++) {
        context.strip.setPixelColor(
            i, Wheel((i + context.iteration) & 255, context));
    }

    addGlitter(context, 5);
    context.strip.show();
    delay(20);
}

void addGlitter(GlobalContext &context, uint8_t chanceOfGlitter) {
    if (randomInt() < chanceOfGlitter) {
        context.strip.setPixelColor(random16(NUM_LEDS), 255, 255, 255);
    }
}

uint8_t randomInt() { return rand() % 101; }
uint16_t random16(uint16_t max) { return rand() % max; }
