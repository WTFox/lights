/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#include "Particle.h"
#line 1 "/Users/anthonyfox/dev/lights/src/main.ino"
#include "GlobalContext.h"
#include "main.h"
#include "neopixel.h"
#include "patterns/allPatterns.h"

void setup();
void loop();
int gotoNextPattern(String command);
int getBrightness(String command);
int setBrightness(String command);
int setPatternDurationMinutes(String command);
int toggleCyclingPatterns(String command);
#line 6 "/Users/anthonyfox/dev/lights/src/main.ino"
#define NUM_LEDS 100
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

    Particle.function("setPatternDurationMinutes", [](String command) {
        context.patternDurationInSeconds = command.toInt() * 60 * 1000;
        return context.patternDurationInSeconds;
    });

    Particle.function("toggleCyclingPatterns", [](String command) {
        context.cyclePatterns = !context.cyclePatterns;
        return context.cyclePatterns;
    });

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
