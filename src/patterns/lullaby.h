#ifndef LULLABY_H
#define LULLABY_H

#include "GlobalContext.h"
#include "main.h"

#define LULLABY_MAX_BRIGHTNESS 150
#define LULLABY_MIN_BRIGHTNESS 10
#define LULLABY_FADE_AMOUNT 1

extern int lullabyFadeDirection;

void lullabySetup(GlobalContext &context);
void lullabyLoop(GlobalContext &context);

#endif