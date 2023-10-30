#include "patterns.h"

Pattern patterns[] = {
    {
        coloredSparkleSetup,
        coloredSparkleLoop,
        "coloredSparkle",
        PatternArgs{
            .primary_color = 0xff3300,
            .sparkle_color = 0x00ff00,
            .chance_of_sparkle = 80,
        },
    },
    {
        coloredSparkleFadeSetup,
        coloredSparkleFadeLoop,
        "coloredSparkleFade",
        PatternArgs{
            .primary_color = 0xff3300,
            .sparkle_color = 0x00ff00,
            .chance_of_sparkle = 5,
        },
    },
    {
        coloredSparkleSetup,
        coloredSparkleLoop,
        "coloredSparkle2",
        PatternArgs{
            .primary_color = 0x0011ff,
            .sparkle_color = 0xff00a6,
            .chance_of_sparkle = 80,
        },
    },
    {
        coloredSparkleFadeSetup,
        coloredSparkleFadeLoop,
        "coloredSparkleFade2",
        PatternArgs{
            .primary_color = 0x0011ff,
            .sparkle_color = 0xff00a6,
            .chance_of_sparkle = 5,
        },
    },
    {
        dynamicGlowSetup,
        dynamicGlowLoop,
        "fireplace",
        PatternArgs{
            .primary_color = 0xff5a00,
            .intensity = 100,
        },
    },
    {
        dynamicGlowSetup,
        dynamicGlowLoop,
        "arcReactor",
        PatternArgs{
            .primary_color = 0x0055ff,
            .intensity = 100,
        },
    },
    {
        rainbowSetup,
        rainbowLoop,
        "rainbow",
        PatternArgs{
            .chance_of_sparkle = 0,
        },
    },
    {
        rainbowSetup,
        rainbowLoop,
        "rainbow",
        PatternArgs{
            .sparkle_color = 0xffffff,
            .chance_of_sparkle = 25,
        },
    },
    {nightSkySetup, nightSkyLoop, "nightSky", {}},
    {lullabySetup, lullabyLoop, "lullaby", {}},
    {christmasRainbowSetup, christmasRainbowLoop, "christmasRainbow", {}},
    {
        christmasRainbowSetup,
        christmasRainbowLoop,
        "christmasRainbow",
        PatternArgs{
            .sparkle_color = 0xffffff,
            .chance_of_sparkle = 25,
        },
    },
    {christmasWaveSetup, christmasWaveLoop, "christmasWave", {}},
};

Color::Color() : r(0), g(0), b(0) {}

Color::Color(uint32_t value)
    : r((value >> 16) & 0xFF), g((value >> 8) & 0xFF), b(value & 0xFF) {}

int lookupPatternByName(String name) {
    for (int i = 0; i < sizeof(patterns) / sizeof(patterns[0]); i++) {
        if (patterns[i].name == name) {
            return i;
        }
    }
    return -1;
}

void setPattern(GlobalContext &context, int patternIndex) {
    context.currentPattern = patternIndex;
    context.iteration = 0;
    context.lastPatternChange = millis();
    context.currentPatternName = patterns[patternIndex].name;
    patterns[patternIndex].setupFunc(context, patterns[patternIndex].args);
}
