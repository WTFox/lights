#ifndef GLOBAL_CONTEXT_H
#define GLOBAL_CONTEXT_H

#include "neopixel.h"
struct GlobalContext {
    int brightness;
    int currentPattern;
    int patternDurationInSeconds;
    int lastPatternChange;
    uint8_t iteration;
    Adafruit_NeoPixel strip;
    bool cyclePatterns;
};

#endif
