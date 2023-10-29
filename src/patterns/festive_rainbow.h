#ifndef FESTIVE_RAINBOW_H
#define FESTIVE_RAINBOW_H

#include "global_context.h"
#include "main_ino.h"

uint32_t festiveWheel(byte WheelPos, Adafruit_NeoPixel &strip);
void festiveRainbowSetup(GlobalContext &context);
void festiveRainbowLoop(GlobalContext &context);

#endif
