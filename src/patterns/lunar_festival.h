#ifndef PATTERNS_LUNAR_FESTIVAL_H
#define PATTERNS_LUNAR_FESTIVAL_H

#include "global_context.h"
#include "patterns.h"

#define LUNAR_WAVE_SPEED 10 
#define LUNAR_WAVE_WIDTH 10 
#define MAX_BRIGHTNESS 255
#define MIN_BRIGHTNESS 50
#define INTERPOLATION_STEPS 225  

void lunarFestivalSetup(GlobalContext &context, PatternArgs &args);
void lunarFestivalLoop(GlobalContext &context, PatternArgs &args);

#endif
