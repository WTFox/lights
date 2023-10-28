#ifndef RAINBOW_GLITTER_H
#define RAINBOW_GLITTER_H

#include "GlobalContext.h"
#include "main_ino.h"
#include "rainbow.h"

void addGlitter(GlobalContext &context, uint8_t chanceOfGlitter);

void rainbowWithGlitterSetup(GlobalContext &context);
void rainbowWithGlitterLoop(GlobalContext &context);

#endif
