#ifndef PATTERNS_H
#define PATTERNS_H

#include "global_context.h"

struct PatternArgs {
    uint32_t primary_color;
    uint32_t sparkle_color;
    uint8_t chance_of_sparkle = 0;
    uint8_t intensity = 0;
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

extern Pattern patterns[13];

int lookupPatternByName(String name);
void setPattern(GlobalContext &context, int patternIndex);

#include "patterns/christmas_rainbow.h"
#include "patterns/christmas_wave.h"
#include "patterns/colored_sparkle.h"
#include "patterns/colored_sparkle_fade.h"
#include "patterns/dynamic_glow.h"
#include "patterns/lullaby.h"
#include "patterns/night_sky.h"
#include "patterns/rainbow.h"

#endif
