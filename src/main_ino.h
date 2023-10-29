#ifndef MAIN_INO_H
#define MAIN_INO_H

#ifndef NUM_LEDS
#define NUM_LEDS 100
#endif

#include "global_context.h"
#include "neopixel.h"
#include "patterns/all_patterns.h"

#ifndef ARRAY_SIZE
#define ARRAY_SIZE(A) (sizeof(A) / sizeof((A)[0]))
#endif

#ifndef MATH_FUNCTIONS
#define PI 3.1415926535897932384626433832795
#endif

typedef void (*PatternFunction)();

struct Pattern {
    void (*setupFunc)(GlobalContext &);
    void (*loopFunc)(GlobalContext &);
    String name;
};

uint8_t randomInt();
uint16_t random16(uint16_t max);

#endif
