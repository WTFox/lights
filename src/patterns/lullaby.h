#ifndef LULLABY_H
#define LULLABY_H

#include "global_context.h"
#include "main_ino.h"

#define LULLABY_MAX_BRIGHTNESS 150
#define LULLABY_MIN_BRIGHTNESS 10
#define LULLABY_FADE_AMOUNT 1

extern int lullabyFadeDirection;

void lullabySetup(GlobalContext &context, PatternArgs &args);
void lullabyLoop(GlobalContext &context, PatternArgs &args);

#endif
