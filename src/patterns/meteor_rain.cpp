#include "meteor_rain.h"

void meteorRainSetup(GlobalContext &context, PatternArgs &args) {
    for (int i = 0; i < context.strip.numPixels(); i++) {
        context.strip.setPixelColor(i, 0, 0, 0);
    }
    context.strip.show();
}

void meteorRainLoop(GlobalContext &context, PatternArgs &args) {
    static float position = -METEOR_SIZE;
    Color meteorColor(args.primary_color);    // Orange
    Color decayColor(args.secondary_color);   // Red
    
    // Fade all pixels
    for(int i = 0; i < context.strip.numPixels(); i++) {
        Color current = Color(context.strip.getPixelColor(i)).toGRB();
        float fade_factor = (float)(255 - METEOR_DECAY) / 255.0;
        uint8_t r = current.r * fade_factor;
        uint8_t g = current.g * fade_factor;
        uint8_t b = current.b * fade_factor;
        context.strip.setPixelColor(i, Color(((uint32_t)r << 16) | ((uint32_t)g << 8) | b).toGRB());
    }
    
    // Draw meteor
    for(int i = 0; i < METEOR_SIZE; i++) {
        int pixelPos = (int)position + i;
        if(pixelPos >= 0 && pixelPos < context.strip.numPixels()) {
            context.strip.setPixelColor(pixelPos, meteorColor.toGRB());
        }
    }
    
    // Random sparks in the trail with decay color
    if(args.chance_of_sparkle > 0) {
        for(int i = 0; i < METEOR_TRAIL; i++) {
            float trailPos = position - i;
            if(trailPos >= 0 && trailPos < context.strip.numPixels() && random(100) < args.chance_of_sparkle) {
                context.strip.setPixelColor((int)trailPos, decayColor.toGRB());
            }
        }
    }
    
    position += 0.1; // Much smaller increment for smoother movement
    if(position > context.strip.numPixels() + METEOR_SIZE) {
        position = -METEOR_SIZE;
    }
    
    context.strip.show();
    delay(METEOR_SPEED / 2); // Adjusted delay
} 