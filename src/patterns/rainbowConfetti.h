#ifndef RAINBOWCONFETTI_H
#define RAINBOWCONFETTI_H

#include "GlobalContext.h"
#include "main.h"

#define RAINBOW_CONFETTI_CHANCE 5
#define RAINBOW_CONFETTI_FADE_AMOUNT 10

extern int confettiColorChange[];

void rainbowConfettiSetup(GlobalContext &context);
void rainbowConfettiLoop(GlobalContext &context);

#endif
