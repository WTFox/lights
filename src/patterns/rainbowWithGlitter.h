#ifndef RAINBOW_GLITTER_H
#define RAINBOW_GLITTER_H

#include "GlobalContext.h"
#include "main.h"
#include "rainbow.h"

uint8_t randomInt();
uint16_t random16(uint16_t max);

void addGlitter(GlobalContext &context, uint8_t chanceOfGlitter);

void rainbowWithGlitterSetup(GlobalContext &context);
void rainbowWithGlitterLoop(GlobalContext &context);

#endif
