#ifndef GLOBAL_CONTEXT_H
#define GLOBAL_CONTEXT_H

#include "neopixel.h"
struct GlobalContext {
    int brightness;
    int alertBrightness;
    int currentPattern;
    Adafruit_NeoPixel strip;
};

#endif // GLOBAL_CONTEXT_H
