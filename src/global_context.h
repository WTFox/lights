#ifndef GLOBAL_CONTEXT_H
#define GLOBAL_CONTEXT_H

#include "neopixel.h"

namespace Events {
enum class Type {
    None,
    Alert,
};
}; // namespace Events

struct GlobalContext {
    int brightness;
    int nightTimeBrightness;
    int alertBrightness;
    int currentPattern;
    int patternDurationInSeconds;
    int lastPatternChange;
    uint8_t iteration;
    Adafruit_NeoPixel strip;
    bool cyclePatterns;
    bool nightModeActive;
    unsigned long lastEventStart = 0;
    Events::Type event_type = Events::Type::None;
    String currentPatternName;
    String currentTagFilter;
    uint32_t alertColor;
};

#endif
