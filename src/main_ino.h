#pragma once

#include "patterns.h"

#ifndef NUM_LEDS
#define NUM_LEDS 100
#endif

#ifndef ARRAY_SIZE
#define ARRAY_SIZE(A) (sizeof(A) / sizeof((A)[0]))
#endif

#ifndef MATH_FUNCTIONS
#define PI 3.1415926535897932384626433832795
#endif

uint8_t randomInt();
uint16_t random16(uint16_t max);
