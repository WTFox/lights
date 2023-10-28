#ifndef RAINBOW_H
#define RAINBOW_H

#include "GlobalContext.h"
#include "main_ino.h"

void rainbowSetup(GlobalContext &context);
void rainbowLoop(GlobalContext &context);
uint32_t Wheel(byte WheelPos, GlobalContext &context);

#endif
