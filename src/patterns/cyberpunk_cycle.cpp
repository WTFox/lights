#include "cyberpunk_cycle.h"

#define CYCLE_DELAY 25

const uint32_t CyberColors[] = {
    0x000080, // Deep Blue
    0x0000BF, // Mid Blue
    0x007BFF, // Electric Blue
    0x4B0082, // Deep Purple
    0x8A2BE2, // Violet
    0xFF1493, // Deep Pink
    0xFF69B4, // Bright Pink
    0xFFB6C1  // Lighter Pink
};

const uint8_t numColors = sizeof(CyberColors) / sizeof(uint32_t);

uint32_t GetCyberColor(GlobalContext &context, uint8_t index) {
    return CyberColors[index % numColors];
}

void cyberpunkCycleSetup(GlobalContext &context, PatternArgs &args) {
    // Initial setup can be empty for this pattern.
}

void cyberpunkCycleLoop(GlobalContext &context, PatternArgs &args) {
    uint16_t i, j;

    for (j = 0; j < 256 * numColors; j++) {
        for (i = 0; i < context.strip.numPixels(); i++) {
            uint32_t color = CyberWheel(context, (i * numColors + j) & 255);
            uint8_t r = (color >> 16) & 0xFF;
            uint8_t g = (color >> 8) & 0xFF;
            uint8_t b = color & 0xFF;

            context.strip.setPixelColor(i, g, r, b);
        }
        context.strip.show();
        delay(CYCLE_DELAY);
    }
}

uint32_t CyberWheel(GlobalContext &context, uint8_t WheelPos) {
    WheelPos = 255 - WheelPos;
    if (WheelPos < 85) {
        return context.strip.Color((WheelPos * 3) / 2, 0, 255 - WheelPos * 3);
    }
    if (WheelPos < 170) {
        WheelPos -= 85;
        return context.strip.Color((255 - WheelPos * 3) / 2, 0, WheelPos * 3);
    }
    WheelPos -= 170;
    return context.strip.Color(0, WheelPos * 3, (255 - WheelPos * 3) / 2);
}
