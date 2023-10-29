#pragma once

#include "global_context.h"
#include "main_ino.h"

void rainbowSetup(GlobalContext &context, PatternArgs &args);
void rainbowLoop(GlobalContext &context, PatternArgs &args);
uint32_t Wheel(byte WheelPos, GlobalContext &context);
