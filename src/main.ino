#include "GlobalContext.h"
#include "main.h"
#include "neopixel.h"
#include "patterns/allPatterns.h"

#define DATA_PIN D5
#define LED_TYPE WS2811

GlobalContext context = {
    .brightness = 150,
    .currentPattern = 0,
    .patternDurationInSeconds = 15 * 60 * 1000,
    .lastPatternChange = 0,
    .iteration = 0,
    .strip = Adafruit_NeoPixel(NUM_LEDS, DATA_PIN, LED_TYPE),
    .cyclePatterns = false,
};

Pattern patterns[] = {
    {halloweenSetup, halloweenLoop, "halloween"},
    {halloween2Setup, halloween2Loop, "halloween2"},
    // {confettiSetup, confettiLoop, "confetti"},
    {rainbowWithGlitterSetup, rainbowWithGlitterLoop, "rainbowWithGlitter"},
    {rainbowSetup, rainbowLoop, "rainbow"},
    {fireplaceSetup, fireplaceLoop, "fireplace"},
    {christmasWaveSetup, christmasWaveLoop, "christmasWave"},
    {festiveRainbowSetup, festiveRainbowLoop, "festiveRainbow"},
    {twinkleSetup, twinkleLoop, "twinkle"},
};

String currentPatternName = "";

void setup() {
    Particle.variable("currentPattern", currentPatternName);

    Particle.function("getBrightness", getBrightness);
    Particle.function("setBrightness", setBrightness);
    Particle.function("nextPattern", gotoNextPattern);
    Particle.function("setPatternDurationMinutes", setPatternDurationMinutes);
    Particle.function("toggleCyclingPatterns", toggleCyclingPatterns);

    context.strip.begin();
    context.strip.show();
    patterns[context.currentPattern].setupFunc(context);
}

void loop() {
    context.strip.setBrightness(context.brightness);
    patterns[context.currentPattern].loopFunc(context);

    if (context.cyclePatterns) {
        if (millis() - context.lastPatternChange >=
            static_cast<unsigned long>(context.patternDurationInSeconds)) {
            gotoNextPattern("");
            context.lastPatternChange = millis();
        }
    }

    context.iteration++;
    currentPatternName = patterns[context.currentPattern].name;
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

uint8_t randomInt() { return rand() % 101; }
uint16_t random16(uint16_t max) { return rand() % max; }
