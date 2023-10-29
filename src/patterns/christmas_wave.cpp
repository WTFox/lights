#include "christmas_wave.h"

#define WAVE_SPEED 1000 // Speed of the wave propagation
#define WAVE_WIDTH 3    // Width of the wave

void christmasWaveSetup(GlobalContext &context) {
    for (int i = 0; i < NUM_LEDS; i++) {
        context.strip.setPixelColor(i, 0, 0, 0);
    }
}

void christmasWaveLoop(GlobalContext &context) {
    static uint16_t pos = 0; // Current position in the wave

    for (uint16_t i = 0; i < context.strip.numPixels(); i++) {
        // Calculate a value between -1 and 1 based on a sine wave
        float level = sin((i + pos) * 1.0 / WAVE_WIDTH * PI);

        if (level > 0.5) {
            // Red for the top half of the wave
            uint8_t r = 255;
            uint8_t g = 0;
            uint8_t b = 0;
            context.strip.setPixelColor(i, context.strip.Color(g, r, b));
        } else if (level < -0.5) {
            // Green for the bottom half of the wave
            uint8_t r = 0;
            uint8_t g = 255;
            uint8_t b = 0;
            context.strip.setPixelColor(i, context.strip.Color(g, r, b));
        } else {
            // White in the middle of the wave
            uint8_t r = 255;
            uint8_t g = 255;
            uint8_t b = 255;
            context.strip.setPixelColor(i, context.strip.Color(g, r, b));
        }
    }

    pos++; // Move the wave position for the next frame
    if (pos > (WAVE_WIDTH * PI))
        pos = 0; // Reset the wave position if necessary

    context.strip.show();
    delay(WAVE_SPEED);
}
