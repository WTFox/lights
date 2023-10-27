#ifndef CONFETTI_H
#define CONFETTI_H

#include "GlobalContext.h"
#include "main.h"

#define CONFETTI_UPDATE_INTERVAL 200 // Update interval in milliseconds
#define CONFETTI_CHANCE                                                        \
    10 // Chance (out of 100) that a new confetti pixel will light up
#define CONFETTI_FADE_AMOUNT 2 // Amount to fade each step for smoothness

extern int confettiBrightness[];
extern int confettiFadeDirection[];

void confettiSetup(GlobalContext &context);
void confettiLoop(GlobalContext &context);

#endif
