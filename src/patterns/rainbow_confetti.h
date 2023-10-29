#pragma once

#include "global_context.h"
#include "main_ino.h"

#define RAINBOW_CONFETTI_CHANCE 5
#define RAINBOW_CONFETTI_FADE_AMOUNT 10

extern int confettiColorChange[];

void rainbowConfettiSetup(GlobalContext &context, PatternArgs &args);
void rainbowConfettiLoop(GlobalContext &context, PatternArgs &args);
