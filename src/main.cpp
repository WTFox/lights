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
#line 6 "/Users/anthonyfox/dev/lights/src/main.ino"
#define NUM_LEDS 100
#define DATA_PIN D5
#define LED_TYPE WS2811

GlobalContext context = {
    .brightness = 150,
    .alertBrightness = 255,
    .currentPattern = 0,
    .patternDurationInSeconds = 5 * 1000,
    .lastPatternChange = 0,
    .iteration = 0,
    .strip = Adafruit_NeoPixel(NUM_LEDS, DATA_PIN, LED_TYPE),
};

Pattern patterns[] = {
    {twinkleSetup, twinkleLoop, "twinkle"},
    {fireplaceSetup, fireplaceLoop, "fireplace"},
    {christmasWaveSetup, christmasWaveLoop, "christmasWave"},
    {rainbowSetup, rainbowLoop, "rainbow"},
    {rainbowWithGlitterSetup, rainbowWithGlitterLoop, "rainbowWithGlitter"},
    {festiveRainbowSetup, festiveRainbowLoop, "festiveRainbow"}};

void setup() {
    Particle.function("getBrightness", getBrightness);
    Particle.function("setBrightness", setBrightness);
    Particle.function("nextPattern", gotoNextPattern);

    context.strip.begin();
    context.strip.show();
    patterns[context.currentPattern].setupFunc(context);
}

void loop() {
    context.strip.setBrightness(context.brightness);
    patterns[context.currentPattern].loopFunc(context);

    if (millis() - context.lastPatternChange >= static_cast<unsigned long>(context.patternDurationInSeconds)) {
        context.currentPattern =
            (context.currentPattern + 1) % ARRAY_SIZE(patterns);
        patterns[context.currentPattern].setupFunc(context);
        context.lastPatternChange = millis();
    }

    context.iteration++;
}

int gotoNextPattern(String command) {
    context.currentPattern =
        (context.currentPattern + 1) % ARRAY_SIZE(patterns);
    return 1;
}

int getBrightness(String command) { return context.brightness; }
int setBrightness(String command) {
    context.brightness = command.toInt();
    return context.brightness;
}
