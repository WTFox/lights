#pragma once

#include "neopixel.h"

struct GlobalContext {
    int brightness;
    int nightTimeBrightness;
    int currentPattern;
    int patternDurationInSeconds;
    int lastPatternChange;
    uint8_t iteration;
    Adafruit_NeoPixel strip;
    bool cyclePatterns;
    bool nightTime;
};
