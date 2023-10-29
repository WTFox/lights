#pragma once

#include "global_context.h"
#include "main_ino.h"
#include "patterns.h"

#define CONFETTI_UPDATE_INTERVAL 200 // Update interval in milliseconds
#define CONFETTI_CHANCE                                                        \
    10 // Chance (out of 100) that a new confetti pixel will light up
#define CONFETTI_FADE_AMOUNT 2 // Amount to fade each step for smoothness

extern int confettiBrightness[];
extern int confettiFadeDirection[];

void confettiSetup(GlobalContext &context, PatternArgs &args);
void confettiLoop(GlobalContext &context, PatternArgs &args);
