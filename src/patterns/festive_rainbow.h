#pragma once

#include "global_context.h"
#include "main_ino.h"

uint32_t festiveWheel(byte WheelPos, Adafruit_NeoPixel &strip);
void festiveRainbowSetup(GlobalContext &context, PatternArgs &args);
void festiveRainbowLoop(GlobalContext &context, PatternArgs &args);
