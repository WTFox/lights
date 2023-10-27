#ifndef HALLOWEEN2_H
#define HALLOWEEN2_H

#include "GlobalContext.h"
#include "main.h"

#define HALLOWEEN_2_GREEN_BEAD_CHANCE 5
#define HALLOWEEN_2_FADE_AMOUNT 5
#define HALLOWEEN_2_MAX_GREEN_BRIGHTNESS 255

extern int halloween2BeadBrightness[]; // Brightness level for each green bead.
extern int
    halloween2FadeDirection[]; // Direction in which the bead is currently
                               // fading: 1 for in, -1 for out, 0 for no fade.

void halloween2Setup(GlobalContext &context);
void halloween2Loop(GlobalContext &context);

#endif
