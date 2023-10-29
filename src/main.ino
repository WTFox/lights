#include "main_ino.h"

#define PIXEL_TYPE WS2812B
#if (PLATFORM_ID == 32)
// Photon2
#define PIXEL_PIN SPI1
#else
#define PIXEL_PIN D5
#endif

GlobalContext context = {
    .brightness = 150,
    .currentPattern = 0,
    .patternDurationInSeconds = 15 * 60 * 1000,
    .lastPatternChange = 0,
    .iteration = 0,
    .strip = Adafruit_NeoPixel(NUM_LEDS, PIXEL_PIN, PIXEL_TYPE),
    .cyclePatterns = false,
};

Pattern patterns[] = {
    {
        coloredSparkleSetup,
        coloredSparkleLoop,
        "coloredSparkle",
        PatternArgs{
            .primary_color = 0xff3300,
            .sparkle_color = 0x00ff00,
            .with_sparkles = true,
            .chance_of_sparkle = 80,
        },
    },
    {
        coloredSparkleSetup,
        coloredSparkleLoop,
        "coloredSparkle2",
        PatternArgs{
            .primary_color = 0x0011ff,
            .sparkle_color = 0xff00a6,
            .with_sparkles = true,
            .chance_of_sparkle = 80,
        },
    },
    {halloween2Setup, halloween2Loop, "halloween2", {}},
    // {fireplaceSetup, fireplaceLoop, "fireplace", {}},
    // {rainbowWithGlitterSetup, rainbowWithGlitterLoop, "rainbowWithGlitter",
    // {}}, {rainbowSetup, rainbowLoop, "rainbow", {}}, {nightSkySetup,
    // nightSkyLoop, "nightSky", {}}, {cyberpunkCycleSetup, cyberpunkCycleLoop,
    // "cyberpunkCycle", {}}, {festiveRainbowSetup, festiveRainbowLoop,
    // "festiveRainbow", {}}, {christmasWaveSetup, christmasWaveLoop,
    // "christmasWave", {}}, {lullabySetup, lullabyLoop, "lullaby", {}},
    // {rainbowConfettiSetup, rainbowConfettiLoop, "rainbowConfetti", {}},
    // {confettiSetup, confettiLoop, "confetti", {}},
};

String currentPatternName = "";

void setup() {
    Particle.variable("currentPattern", currentPatternName);

    Particle.function("getBrightness", getBrightness);
    Particle.function("setBrightness", setBrightness);
    Particle.function("nextPattern", gotoNextPattern);
    Particle.function("setPatternDurationMinutes", setPatternDurationMinutes);
    Particle.function("toggleCyclingPatterns", toggleCyclingPatterns);
    Particle.function("toggleNightTime", toggleNightTime);

    context.strip.begin();
    context.strip.show();
    context.strip.setBrightness(context.brightness);
    patterns[context.currentPattern].setupFunc(
        context, patterns[context.currentPattern].args);
}

void loop() {
    patterns[context.currentPattern].loopFunc(
        context, patterns[context.currentPattern].args);
    if (context.cyclePatterns) {
        if (millis() - context.lastPatternChange >=
            static_cast<unsigned long>(context.patternDurationInSeconds)) {
            gotoNextPattern("");
            context.lastPatternChange = millis();
        }
    }

    currentPatternName = patterns[context.currentPattern].name;
    context.iteration++;
}

int gotoNextPattern(String command) {
    context.currentPattern =
        (context.currentPattern + 1) % ARRAY_SIZE(patterns);
    patterns[context.currentPattern].setupFunc(
        context, patterns[context.currentPattern].args);
    return 1;
}

// region ParticleFunctions
int getBrightness(String command) { return context.brightness; }
int setBrightness(String command) {
    context.brightness = command.toInt();
    context.strip.setBrightness(context.brightness);
    return context.brightness;
}

int setPatternDurationMinutes(String command) {
    context.patternDurationInSeconds = command.toInt() * 60 * 1000;
    return context.patternDurationInSeconds / 1000 / 60;
}

int toggleCyclingPatterns(String command) {
    context.cyclePatterns = !context.cyclePatterns;
    return 1;
}

int toggleNightTime(String command) {
    context.nightTime = !context.nightTime;
    return 1;
}
// endregion

uint8_t randomInt() { return rand() % 101; }
uint16_t random16(uint16_t max) { return rand() % max; }
