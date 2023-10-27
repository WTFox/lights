#include "christmasWave.h"
#include "math.h"

#define PI 3.1415926535897932384626433832795
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
            context.strip.setPixelColor(i, context.strip.Color(255, 0, 0));
        } else if (level < -0.5) {
            // Green for the bottom half of the wave
            context.strip.setPixelColor(i, context.strip.Color(0, 255, 0));
        } else {
            // White in the middle of the wave
            context.strip.setPixelColor(i, context.strip.Color(255, 255, 255));
        }
    }

    pos++; // Move the wave position for the next frame
    if (pos > (WAVE_WIDTH * PI))
        pos = 0; // Reset the wave position if necessary

    context.strip.show();
    delay(WAVE_SPEED);
}
