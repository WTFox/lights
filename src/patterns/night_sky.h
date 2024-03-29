#ifndef PATTERNS_NIGHT_SKY_H
#define PATTERNS_NIGHT_SKY_H

#include "global_context.h"
#include "patterns.h"

// Chance (out of 100) for a star to start twinkling
#define NIGHTSKY_STAR_CHANCE 3
#define NIGHTSKY_MAX_BRIGHTNESS 150
#define NIGHTSKY_MIN_BRIGHTNESS 5
#define NIGHTSKY_FADE_AMOUNT 1

extern int nightSkyBrightness[];
extern int nightSkyFadeDirection[];

void nightSkySetup(GlobalContext &context, PatternArgs &args);
void nightSkyLoop(GlobalContext &context, PatternArgs &args);

#endif
