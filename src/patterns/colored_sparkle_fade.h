#ifndef COLORED_SPARKLE_FADE
#define COLORED_SPARKLE_FADE

#include "global_context.h"
#include "main_ino.h"

#define FADE_AMOUNT 5

// Brightness level for each green bead.
extern int beadBrightness[];

// Direction in which the bead is currently
// fading: 1 for in, -1 for out, 0 for no fade.
extern int fadeDirection[];

void coloredSparkleFadeSetup(GlobalContext &context, PatternArgs &args);
void coloredSparkleFadeLoop(GlobalContext &context, PatternArgs &args);

#endif
