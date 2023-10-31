#include "patterns.h"

std::vector<Pattern> patterns = {
    {coloredSparkleSetup,
     coloredSparkleLoop,
     "coloredSparkle",
     PatternArgs{
         .primary_color = 0xff3300,
         .sparkle_color = 0x00ff00,
         .chance_of_sparkle = 80,
     },
     {"halloween"}},
    {coloredSparkleFadeSetup,
     coloredSparkleFadeLoop,
     "coloredSparkleFade",
     PatternArgs{
         .primary_color = 0xff3300,
         .sparkle_color = 0x00ff00,
         .chance_of_sparkle = 5,
     },
     {"halloween"}},
    {
        coloredSparkleSetup,
        coloredSparkleLoop,
        "coloredSparkle2",
        PatternArgs{
            .primary_color = 0x0011ff,
            .sparkle_color = 0xff00a6,
            .chance_of_sparkle = 80,
        },
        {},
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
        {},
    },
    {
        dynamicGlowSetup,
        dynamicGlowLoop,
        "fireplace",
        PatternArgs{
            .primary_color = 0xff5a00,
            .intensity = 100,
        },
        {"halloween", "night"},
    },
    {
        dynamicGlowSetup,
        dynamicGlowLoop,
        "arcReactor",
        PatternArgs{
            .primary_color = 0x0055ff,
            .intensity = 100,
        },
        {},
    },
    {
        rainbowSetup,
        rainbowLoop,
        "rainbow",
        PatternArgs{
            .chance_of_sparkle = 0,
        },
        {},
    },
    {
        rainbowSetup,
        rainbowLoop,
        "rainbow",
        PatternArgs{
            .sparkle_color = 0xffffff,
            .chance_of_sparkle = 25,
        },
        {},
    },
    {
        nightSkySetup,
        nightSkyLoop,
        "nightSky",
        {},
        {"night"},
    },
    {
        lullabySetup,
        lullabyLoop,
        "lullaby",
        {},
        {"night"},
    },
    {
        christmasRainbowSetup,
        christmasRainbowLoop,
        "christmasRainbow",
        {},
        {"christmas"},
    },
    {
        christmasRainbowSetup,
        christmasRainbowLoop,
        "christmasRainbow",
        PatternArgs{
            .sparkle_color = 0xffffff,
            .chance_of_sparkle = 25,
        },
        {"christmas"},
    },
    {
        christmasWaveSetup,
        christmasWaveLoop,
        "christmasWave",
        {},
        {"christmas"},
    },
};

std::vector<Pattern> filterPatternsByTag(const std::vector<Pattern> &patterns,
                                         const String &tag) {

    if (tag == "" || tag == "all") {
        return patterns;
    }

    std::vector<Pattern> filteredPatterns;
    for (int i = 0; i < patterns.size(); i++) {
        for (int j = 0; j < patterns[i].tags.size(); j++) {
            if (patterns[i].tags[j] == tag) {
                filteredPatterns.push_back(patterns[i]);
                break;
            }
        }
    }

    if (filteredPatterns.size() == 0) {
        return patterns;
    }
    return filteredPatterns;
}

Color::Color() : r(0), g(0), b(0) {}

Color::Color(uint32_t value)
    : r((value >> 16) & 0xFF), g((value >> 8) & 0xFF), b(value & 0xFF) {}

int lookupPatternByName(String name) {
    for (int i = 0; i < patterns.size(); i++) {
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
