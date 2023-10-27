#ifndef FESTIVE_RAINBOW_H
#define FESTIVE_RAINBOW_H

#include "GlobalContext.h"
#include "main.h"

uint32_t festiveWheel(byte WheelPos, Adafruit_NeoPixel &strip);
void festiveRainbowSetup(GlobalContext &context);
void festiveRainbowLoop(GlobalContext &context);

#endif
