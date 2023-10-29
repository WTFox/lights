#ifndef PATTERNS_FIREPLACE_H
#define PATTERNS_FIREPLACE_H

#include "global_context.h"
#include "main_ino.h"

// TODO: move this to PatternArgs.intensity
#define FIRE_INTENSITY 75

void fireplaceSetup(GlobalContext &context, PatternArgs &args);
void fireplaceLoop(GlobalContext &context, PatternArgs &args);

#endif
