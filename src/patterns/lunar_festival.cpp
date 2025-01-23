#include "lunar_festival.h"

void lunarFestivalSetup(GlobalContext &context, PatternArgs &args) {
    for (int i = 0; i < context.strip.numPixels(); i++) {
        context.strip.setPixelColor(i, 0, 0, 0);
    }
    context.strip.show();
}

void lunarFestivalLoop(GlobalContext &context, PatternArgs &args) {
    static uint16_t position = 0;
    static float offset = 0;
    
    Color red(args.primary_color);  
    Color gold(args.secondary_color);   
    
    offset += 0.05;  // Smaller increment for smoother movement
    
    for (int i = 0; i < context.strip.numPixels(); i++) {
        // Create a flowing wave pattern with smoother sine wave
        float wave = sin((i + offset) * 2 * PI / LUNAR_WAVE_WIDTH);
        float brightness = (wave + 1) * (MAX_BRIGHTNESS - MIN_BRIGHTNESS) / 2 + MIN_BRIGHTNESS;
        
        // Calculate color interpolation factor with smoother transition
        float interpolationFactor = (sin((i + offset) * PI / LUNAR_WAVE_WIDTH) + 1) / 2;
        
        // Smooth out the interpolation factor
        interpolationFactor = (interpolationFactor * interpolationFactor * (3 - 2 * interpolationFactor));
        
        // Interpolate between red and gold with improved precision
        uint8_t r = round(red.r * (1 - interpolationFactor) + gold.r * interpolationFactor);
        uint8_t g = round(red.g * (1 - interpolationFactor) + gold.g * interpolationFactor);
        uint8_t b = round(red.b * (1 - interpolationFactor) + gold.b * interpolationFactor);
        
        // Apply brightness modulation with improved precision
        r = round((r * brightness) / MAX_BRIGHTNESS);
        g = round((g * brightness) / MAX_BRIGHTNESS);
        b = round((b * brightness) / MAX_BRIGHTNESS);
        
        context.strip.setPixelColor(i, g, r, b);
    }
    
    context.strip.show();
    delay(LUNAR_WAVE_SPEED);
} 