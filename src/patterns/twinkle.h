#ifndef TWINKLE_H
#define TWINKLE_H

#include "GlobalContext.h"
#include "main.h"

#define TWINKLE_CHANCE 10
#define FADE_AMOUNT 1
#define MAX_TWINKLING 10
#define MAX_BRIGHTNESS 200

extern int ledBrightness[];
extern int fadeDirection[];
extern int currentlyTwinkling;

void twinkleSetup(GlobalContext &context);
void twinkleLoop(GlobalContext &context);

#endif
