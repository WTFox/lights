#ifndef NIGHTSKY_H
#define NIGHTSKY_H

#include "GlobalContext.h"
#include "main.h"

#define NIGHTSKY_STAR_CHANCE                                                   \
    3 // Chance (out of 100) for a star to start twinkling
#define NIGHTSKY_MAX_BRIGHTNESS 150
#define NIGHTSKY_MIN_BRIGHTNESS 5
#define NIGHTSKY_FADE_AMOUNT 1

extern int nightSkyBrightness[];
extern int nightSkyFadeDirection[];

void nightSkySetup(GlobalContext &context);
void nightSkyLoop(GlobalContext &context);

#endif
