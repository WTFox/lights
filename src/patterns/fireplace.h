#ifndef FIREPLACE_H
#define FIREPLACE_H

#include "GlobalContext.h"
#include "main_ino.h"

#define FIRE_INTENSITY 75
void fireplaceSetup(GlobalContext &context);
void fireplaceLoop(GlobalContext &context);

#endif
