#ifndef PATTERNS_METEOR_RAIN_H
#define PATTERNS_METEOR_RAIN_H

#include "global_context.h"
#include "patterns.h"

#define METEOR_SIZE 10 
#define METEOR_TRAIL 6
#define METEOR_SPEED 5    
#define METEOR_DECAY 10    

void meteorRainSetup(GlobalContext &context, PatternArgs &args);
void meteorRainLoop(GlobalContext &context, PatternArgs &args);

#endif 