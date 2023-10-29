#pragma once

#include "global_context.h"
#include "main_ino.h"

uint32_t CyberWheel(GlobalContext &context, byte WheelPos);
void cyberpunkCycleSetup(GlobalContext &context, PatternArgs &args);
void cyberpunkCycleLoop(GlobalContext &context, PatternArgs &args);
