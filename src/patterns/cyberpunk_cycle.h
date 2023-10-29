#ifndef CYBERPUNK_CYCLE_H
#define CYBERPUNK_CYCLE_H

#include "global_context.h"
#include "main_ino.h"

uint32_t CyberWheel(GlobalContext &context, byte WheelPos);
void cyberpunkCycleSetup(GlobalContext &context);
void cyberpunkCycleLoop(GlobalContext &context);

#endif
