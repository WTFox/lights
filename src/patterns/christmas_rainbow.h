#ifndef CHRISTMAS_RAINBOW_H
#define CHRISTMAS_RAINBOW_H

#include "global_context.h"
#include "patterns.h"

uint32_t festiveWheel(byte WheelPos, GlobalContext &context);
void christmasRainbowSetup(GlobalContext &context, PatternArgs &args);
void christmasRainbowLoop(GlobalContext &context, PatternArgs &args);

#endif
