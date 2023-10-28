#include "main_ino.h"

// IMPORTANT: Set pixel COUNT, PIN and TYPE
#if (PLATFORM_ID == 32)
// MOSI pin MO
#define PIXEL_PIN SPI1
// MOSI pin D2
// #define PIXEL_PIN SPI1
#else // #if (PLATFORM_ID == 32)
#define PIXEL_PIN D5
#endif

// #define PIXEL_PIN SPI1
#define PIXEL_TYPE WS2812B
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
    {halloweenSetup, halloweenLoop, "halloween"},
    {halloween2Setup, halloween2Loop, "halloween2"},
    {rainbowWithGlitterSetup, rainbowWithGlitterLoop, "rainbowWithGlitter"},
    {rainbowSetup, rainbowLoop, "rainbow"},
    {nightSkySetup, nightSkyLoop, "nightSky"},
    {fireplaceSetup, fireplaceLoop, "fireplace"},
    {christmasWaveSetup, christmasWaveLoop, "christmasWave"},
    {festiveRainbowSetup, festiveRainbowLoop, "festiveRainbow"},
    // {lullabySetup, lullabyLoop, "lullaby"},
    // {twinkleSetup, twinkleLoop, "twinkle"},
    // {rainbowConfettiSetup, rainbowConfettiLoop, "rainbowConfetti"},
    // {confettiSetup, confettiLoop, "confetti"},
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
    patterns[context.currentPattern].setupFunc(context);
}

void loop() {
    patterns[context.currentPattern].loopFunc(context);
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
    patterns[context.currentPattern].setupFunc(context);
    return 1;
}

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

uint8_t randomInt() { return rand() % 101; }
uint16_t random16(uint16_t max) { return rand() % max; }
