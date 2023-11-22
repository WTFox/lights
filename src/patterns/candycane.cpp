#include "candycane.h"

#define STRIPE_WIDTH 4

void candycaneSetup(GlobalContext &context, PatternArgs &args) {
    Color firstColor(args.primary_color);
    for (int i = 0; i < context.strip.numPixels(); i++) {
        context.strip.setPixelColor(i, firstColor.toGRB());
    }
    context.strip.show();
}

void candycaneLoop(GlobalContext &context, PatternArgs &args) {
    static int position = 0;

    Color firstColor(args.primary_color);
    Color secondColor(args.secondary_color);

    for (int i = 0; i < context.strip.numPixels(); i++) {
        if ((i + position) % STRIPE_WIDTH != 0) {
            context.strip.setPixelColor(i, firstColor.toGRB());
        } else {
            context.strip.setPixelColor(i, secondColor.toGRB());
        }
    }
    context.strip.show();

    position++;
    if (position >= STRIPE_WIDTH) {
        position = 0;
    }

    delay(args.delay);
}
