#ifndef PATTERNS_H
#define PATTERNS_H

#include "global_context.h"

struct PatternArgs {
    uint32_t primary_color;
    uint32_t sparkle_color;
    uint8_t chance_of_sparkle = 0;
};

typedef void (*PatternFunction)();

struct Pattern {
    void (*setupFunc)(GlobalContext &, PatternArgs &);
    void (*loopFunc)(GlobalContext &, PatternArgs &);
    String name;
    PatternArgs args;
};

struct Color {
    uint8_t r, g, b;
    Color();
    Color(uint32_t value);
};

#include "patterns/christmas_wave.h"
#include "patterns/colored_sparkle.h"
#include "patterns/colored_sparkle_fade.h"
#include "patterns/confetti.h"
#include "patterns/cyberpunk_cycle.h"
#include "patterns/festive_rainbow.h"
#include "patterns/fireplace.h"
#include "patterns/lullaby.h"
#include "patterns/night_sky.h"
#include "patterns/rainbow.h"
#include "patterns/rainbow_confetti.h"

#endif
