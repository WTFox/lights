#ifndef PATTERNS_H
#define PATTERNS_H

#include "global_context.h"

struct PatternArgs {
    uint32_t primary_color;
    uint32_t secondary_color;
    uint8_t chance_of_sparkle = 0;
    uint8_t intensity = 0;
    int16_t delay = 0;
};

typedef void (*PatternFunction)();

struct Pattern {
    String name;
    void (*setupFunc)(GlobalContext &, PatternArgs &);
    void (*loopFunc)(GlobalContext &, PatternArgs &);
    PatternArgs args;
    std::vector<String> tags;
};

struct Color {
    uint8_t r, g, b;
    Color();
    Color(uint32_t value);
    static Color blend(const Color &color1, const Color &color2, int alpha);
    uint32_t toGRB() const;
};

extern std::vector<Pattern> patterns;
std::vector<Pattern> filterPatternsByTag(const std::vector<Pattern> &patterns,
                                         const String &tag);
int lookupPatternByName(String name);
void setPattern(GlobalContext &context, int patternIndex);

#include "patterns/candycane.h"
#include "patterns/christmas_rainbow.h"
#include "patterns/christmas_wave.h"
#include "patterns/colored_sparkle.h"
#include "patterns/colored_sparkle_fade.h"
#include "patterns/dynamic_glow.h"
#include "patterns/lullaby.h"
#include "patterns/night_sky.h"
#include "patterns/rainbow.h"

#endif
