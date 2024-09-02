#include "patterns.h"

std::vector<Pattern> patterns = {
    {
        .name = "fireplace-darker",
        .setupFunc = dynamicGlowSetup,
        .loopFunc = dynamicGlowLoop,
        .args =
            PatternArgs{
                .primary_color = 0xff3a00,
                .intensity = 100,
            },
        .tags = {"autumn", "christmas", "night", "fun"},
    },
    {
        .name = "fireplace",
        .setupFunc = dynamicGlowSetup,
        .loopFunc = dynamicGlowLoop,
        .args =
            PatternArgs{
                .primary_color = 0xff5A00,
                .intensity = 100,
            },
        .tags = {"autumn", "christmas", "night", "fun"},
    },
    {
        .name = "coloredSparkleFade",
        .setupFunc = coloredSparkleFadeSetup,
        .loopFunc = coloredSparkleFadeLoop,
        .args =
            PatternArgs{
                .primary_color = 0xff0000,
                .secondary_color = 0xFF5A00,
                .chance_of_sparkle = 5,
            },
        .tags = {"autumn", "night"},
    },
    {
        .name = "autumn sparkles",
        .setupFunc = coloredSparkleSetup,
        .loopFunc = coloredSparkleLoop,
        .args =
            PatternArgs{
                .primary_color = 0xff3300,
                .secondary_color = 0xaa00ff,
                .chance_of_sparkle = 70,
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
                .secondary_color = 0xff3300,
                .chance_of_sparkle = 5,
            },
        .tags = {"autumn", "fun"},
    },
    {
        .name = "nightSky",
        .setupFunc = nightSkySetup,
        .loopFunc = nightSkyLoop,
        .args = {},
        .tags = {"night"},
    },
    // {
    //     .name = "coloredSparkleFade",
    //     .setupFunc = coloredSparkleFadeSetup,
    //     .loopFunc = coloredSparkleFadeLoop,
    //     .args =
    //         PatternArgs{
    //             .primary_color = 0xff3300,
    //             .secondary_color = 0x00ff00,
    //             .chance_of_sparkle = 5,
    //         },
    //     .tags = {"autumn"},
    // },
    // {
    //     .name = "rainbow",
    //     .setupFunc = rainbowSetup,
    //     .loopFunc = rainbowLoop,
    //     .args =
    //         PatternArgs{
    //             .chance_of_sparkle = 0,
    //         },
    //     .tags = {"fun", "christmas"},
    // },
    // {
    //     .name = "rainbow sparkles",
    //     .setupFunc = rainbowSetup,
    //     .loopFunc = rainbowLoop,
    //     .args =
    //         PatternArgs{
    //             .secondary_color = 0xffffff,
    //             .chance_of_sparkle = 25,
    //         },
    //     .tags = {"fun", "christmas"},
    // },
    // {
    //     .name = "christmasRainbow",
    //     .setupFunc = christmasRainbowSetup,
    //     .loopFunc = christmasRainbowLoop,
    //     .args = {},
    //     .tags = {"christmas"},
    // },
    // {
    //     .name = "christmasRainbow sparkles",
    //     .setupFunc = christmasRainbowSetup,
    //     .loopFunc = christmasRainbowLoop,
    //     .args =
    //         PatternArgs{
    //             .secondary_color = 0xffffff,
    //             .chance_of_sparkle = 25,
    //         },
    //     .tags = {"christmas"},
    // },
    // {
    //     .name = "christmasWave",
    //     .setupFunc = christmasWaveSetup,
    //     .loopFunc = christmasWaveLoop,
    //     .args = {},
    //     .tags = {"christmas"},
    // },
    // {
    //     .name = "arcReactor",
    //     .setupFunc = dynamicGlowSetup,
    //     .loopFunc = dynamicGlowLoop,
    //     .args =
    //         PatternArgs{
    //             .primary_color = 0x0055ff,
    //             .intensity = 100,
    //         },
    //     .tags = {"fun"},
    // },
    // {
    //     .name = "coloredSparkle2",
    //     .setupFunc = coloredSparkleSetup,
    //     .loopFunc = coloredSparkleLoop,
    //     .args =
    //         PatternArgs{
    //             .primary_color = 0xff00a6,
    //             .secondary_color = 0x0011ff,
    //             .chance_of_sparkle = 80,
    //         },
    //     .tags = {"fun"},
    // },
    // {
    //     .name = "CandyCane",
    //     .setupFunc = candycaneSetup,
    //     .loopFunc = candycaneLoop,
    //     .args =
    //         PatternArgs{
    //             .primary_color = 0xff0000,
    //             .secondary_color = 0xffffff,
    //             .delay = 500,
    //         },
    //     .tags = {"christmas"},
    // },
    // {
    //     .name = "CandyCane",
    //     .setupFunc = candycaneSetup,
    //     .loopFunc = candycaneLoop,
    //     .args =
    //         PatternArgs{
    //             .primary_color = 0xff0000,
    //             .secondary_color = 0x00ff00,
    //             .delay = 500,
    //         },
    //     .tags = {"christmas"},
    // },
    // {
    //     .name = "christmas sparkles",
    //     .setupFunc = coloredSparkleSetup,
    //     .loopFunc = coloredSparkleLoop,
    //     .args =
    //         PatternArgs{
    //             .primary_color = 0xff0000,
    //             .secondary_color = 0x00ff00,
    //             .chance_of_sparkle = 85,
    //         },
    //     .tags = {"christmas"},
    // },
    // {
    //     .name = "red blinks",
    //     .setupFunc = coloredSparkleSetup,
    //     .loopFunc = coloredSparkleLoop,
    //     .args =
    //         PatternArgs{
    //             .primary_color = 0x000000,
    //             .secondary_color = 0xff0000,
    //             .chance_of_sparkle = 95,
    //         },
    //     .tags = {"christmas"},
    // },
    // {
    //     .name = "CandyCane",
    //     .setupFunc = candycaneSetup,
    //     .loopFunc = candycaneLoop,
    //     .args =
    //         PatternArgs{
    //             .primary_color = 0x000000,
    //             .secondary_color = 0xff0000,
    //             .delay = 500,
    //         },
    //     .tags = {"christmas", "night"},
    // },
    // {
    //     .name = "green blinks",
    //     .setupFunc = coloredSparkleSetup,
    //     .loopFunc = coloredSparkleLoop,
    //     .args =
    //         PatternArgs{
    //             .primary_color = 0x000000,
    //             .secondary_color = 0x00ff00,
    //             .chance_of_sparkle = 95,
    //         },
    //     .tags = {"christmas"},
    // },
    // {
    //     .name = "CandyCane",
    //     .setupFunc = candycaneSetup,
    //     .loopFunc = candycaneLoop,
    //     .args =
    //         PatternArgs{
    //             .primary_color = 0x000000,
    //             .secondary_color = 0x00ff00,
    //             .delay = 500,
    //         },
    //     .tags = {"christmas", "night"},
    // },
    // {
    //     .name = "coloredSparkleFade2",
    //     .setupFunc = coloredSparkleFadeSetup,
    //     .loopFunc = coloredSparkleFadeLoop,
    //     .args =
    //         PatternArgs{
    //             .primary_color = 0x0011ff,
    //             .secondary_color = 0xff00a6,
    //             .chance_of_sparkle = 5,
    //         },
    //     .tags = {"fun"},
    // },
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

Color::Color() : r(0), g(0), b(0) {}

Color::Color(uint32_t value)
    : r((value >> 16) & 0xFF), g((value >> 8) & 0xFF), b(value & 0xFF) {}

uint32_t Color::toGRB() const {
    return (static_cast<uint32_t>(g) << 16) | // Green first
           (static_cast<uint32_t>(r) << 8) |  // Then red
           static_cast<uint32_t>(b);          // Finally blue
}

Color Color::blend(const Color &color1, const Color &color2, int alpha) {
    Color blendedColor;
    blendedColor.r = (color1.r * (255 - alpha) + color2.r * alpha) / 255;
    blendedColor.g = (color1.g * (255 - alpha) + color2.g * alpha) / 255;
    blendedColor.b = (color1.b * (255 - alpha) + color2.b * alpha) / 255;
    return blendedColor;
}
