#include "colored_sparkle.h"

void coloredSparkleSetup(GlobalContext &context, PatternArgs &args) {}

void coloredSparkleLoop(GlobalContext &context, PatternArgs &args) {
    Color color = args.primary_color;
    Color secondary_color = args.secondary_color;

    for (int i = 0; i < context.strip.numPixels(); i++) {
        context.strip.setPixelColor(i, color.g, color.r, color.b);
    }

    if (randomInt() < args.chance_of_sparkle) {
        uint16_t lucky_pixel = random16(NUM_LEDS);
        context.strip.setPixelColor(lucky_pixel, secondary_color.g,
                                    secondary_color.r, secondary_color.b);
    }

    context.strip.show();
    delay(100);
}
