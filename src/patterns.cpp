#include "patterns.h"

std::vector<Pattern> patterns = {
    {
        .name = "autumn sparkles",
        .setupFunc = coloredSparkleSetup,
        .loopFunc = coloredSparkleLoop,
        .args =
            PatternArgs{
                .primary_color = 0xff3300,
                .sparkle_color = 0x00ff00,
                .chance_of_sparkle = 70,
            },
        .tags = {"autumn", "fun"},
    },
    {
        .name = "coloredSparkleFade",
        .setupFunc = coloredSparkleFadeSetup,
        .loopFunc = coloredSparkleFadeLoop,
        .args =
            PatternArgs{
                .primary_color = 0xff3300,
                .sparkle_color = 0x00ff00,
                .chance_of_sparkle = 5,
            },
        .tags = {"autumn"},
    },
    {
        .name = "coloredSparkleFade",
        .setupFunc = coloredSparkleFadeSetup,
        .loopFunc = coloredSparkleFadeLoop,
        .args =
            PatternArgs{
                .primary_color = 0x9000ff,
                .sparkle_color = 0xff3300,
                .chance_of_sparkle = 5,
            },
        .tags = {"autumn", "fun"},
    },
    {
        .name = "coloredSparkle2",
        .setupFunc = coloredSparkleSetup,
        .loopFunc = coloredSparkleLoop,
        .args =
            PatternArgs{
                .primary_color = 0xff00a6,
                .sparkle_color = 0x0011ff,
                .chance_of_sparkle = 80,
            },
        .tags = {"fun"},
    },
    {
        .name = "coloredSparkleFade2",
        .setupFunc = coloredSparkleFadeSetup,
        .loopFunc = coloredSparkleFadeLoop,
        .args =
            PatternArgs{
                .primary_color = 0x0011ff,
                .sparkle_color = 0xff00a6,
                .chance_of_sparkle = 5,
            },
        .tags = {"fun"},
    },
    {
        .name = "fireplace",
        .setupFunc = dynamicGlowSetup,
        .loopFunc = dynamicGlowLoop,
        .args =
            PatternArgs{
                .primary_color = 0xff5a00,
                .intensity = 100,
            },
        .tags = {"autumn", "night", "fun"},
    },
    {
        .name = "arcReactor",
        .setupFunc = dynamicGlowSetup,
        .loopFunc = dynamicGlowLoop,
        .args =
            PatternArgs{
                .primary_color = 0x0055ff,
                .intensity = 100,
            },
        .tags = {"night", "fun"},
    },
    {
        .name = "rainbow",
        .setupFunc = rainbowSetup,
        .loopFunc = rainbowLoop,
        .args =
            PatternArgs{
                .chance_of_sparkle = 0,
            },
        .tags = {"fun"},
    },
    {
        .name = "rainbow sparkles",
        .setupFunc = rainbowSetup,
        .loopFunc = rainbowLoop,
        .args =
            PatternArgs{
                .sparkle_color = 0xffffff,
                .chance_of_sparkle = 25,
            },
        .tags = {"fun"},
    },
    {
        .name = "nightSky",
        .setupFunc = nightSkySetup,
        .loopFunc = nightSkyLoop,
        .args = {},
        .tags = {"night"},
    },
    {
        .name = "christmasRainbow",
        .setupFunc = christmasRainbowSetup,
        .loopFunc = christmasRainbowLoop,
        .args = {},
        .tags = {"christmas"},
    },
    {
        .name = "christmasRainbow sparkles",
        .setupFunc = christmasRainbowSetup,
        .loopFunc = christmasRainbowLoop,
        .args =
            PatternArgs{
                .sparkle_color = 0xffffff,
                .chance_of_sparkle = 25,
            },
        .tags = {"christmas"},
    },
    {
        .name = "christmasWave",
        .setupFunc = christmasWaveSetup,
        .loopFunc = christmasWaveLoop,
        .args = {},
        .tags = {"christmas"},
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
    std::vector<Pattern> filtered_patterns =
        filterPatternsByTag(patterns, context.currentTagFilter);

    context.currentPattern = patternIndex;
    context.iteration = 0;
    context.lastPatternChange = millis();
    context.currentPatternName = filtered_patterns[patternIndex].name;

    filtered_patterns[patternIndex].setupFunc(
        context, filtered_patterns[patternIndex].args);
}
