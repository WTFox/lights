#ifndef RAINBOW_H
#define RAINBOW_H

#include "global_context.h"
#include "main_ino.h"

void rainbowSetup(GlobalContext &context);
void rainbowLoop(GlobalContext &context);
uint32_t Wheel(byte WheelPos, GlobalContext &context);

#endif
