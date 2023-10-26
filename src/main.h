#ifndef MAIN_H
#define MAIN_H

#include "neopixel.h"

#ifndef ARRAY_SIZE
#define ARRAY_SIZE(A) (sizeof(A) / sizeof((A)[0]))
#endif

#define NUM_LEDS 100

#endif

/* void FillLEDsFromPaletteColors(CRGBPalette16 currentPalette, Context
 * &context) { */
/*     uint8_t colorIndex = context.iteration; */
/*     for (int i = 0; i < NUM_LEDS; ++i) { */
/*         context.leds[i] = ColorFromPalette(currentPalette, colorIndex, */
/*                                            context.brightness, LINEARBLEND);
 */
/*         colorIndex += 3; */
/*     } */
/* } */
/**/
/* void addGlitter(fract8 chanceOfGlitter, Context &context) { */
/*     if (random8() < chanceOfGlitter) { */
/*         context.leds[random16(context.numLEDs)] += */
/*             CRGB::Gray; // White is too bright */
/*     } */
/* } */
/**/
/* void christmas(Context &context) { */
/*     FillLEDsFromPaletteColors(myChristmasPalette_p, context); */
/*     addGlitter(30, context); */
/* } */
/**/
/* void alternateChristmasColors(Context &context) { */
/*     for (int i = 0; i < context.numLEDs; i++) { */
/*         context.leds[i] = myChristmasPalette_p[(i + context.iteration) % 16];
 */
/*     } */
/*     delay(200); */
/* } */
/**/
/* void rainbow(Context &context) { */
/*     fill_rainbow(context.leds, context.numLEDs, context.hue, 7); */
/* } */
/**/
/* void rainbowWithGlitter(Context &context) { */
/*     rainbow(context); */
/*     addGlitter(80, context); */
/* } */
/**/
/* void confetti(Context &context) { */
/*     // random colored speckles that blink in and fade smoothly */
/*     fadeToBlackBy(context.leds, context.numLEDs, 10); */
/*     int pos = random16(context.numLEDs); */
/*     context.leds[pos] += CHSV(context.hue + random8(64), 200, 255); */
/* } */
/**/
/* void sinelon(Context &context) { */
/*     // a colored dot sweeping back and forth, with fading trails */
/*     fadeToBlackBy(context.leds, context.numLEDs, 20); */
/*     int pos = beatsin16(13, 0, context.numLEDs - 1); */
/*     context.leds[pos] += CHSV(context.hue, 255, 192); */
/* } */
/**/
/* void bpm(Context &context) { */
/*     // colored stripes pulsing at a defined Beats-Per-Minute (BPM) */
/*     uint8_t BeatsPerMinute = 62; */
/*     CRGBPalette16 palette = PartyColors_p; */
/*     uint8_t beat = beatsin8(BeatsPerMinute, 64, 255); */
/*     for (int i = 0; i < context.numLEDs; i++) { // 9948 */
/*         context.leds[i] = ColorFromPalette(palette, context.hue + (i * 2), */
/*                                            beat - context.hue + (i * 10)); */
/*     } */
/* } */
/**/
/* void juggle(Context &context) { */
/*     // eight colored dots, weaving in and out of sync with each other */
/*     fadeToBlackBy(context.leds, context.numLEDs, 20); */
/*     uint8_t dothue = 0; */
/*     for (int i = 0; i < 8; i++) { */
/*         context.leds[beatsin16(i + 7, 0, context.numLEDs - 1)] |= */
/*             CHSV(dothue, 200, 255); */
/*         dothue += 32; */
/*     } */
/* } */
/**/
/* void error(Context &context) { */
/*     FastLED.setBrightness(gContext.alertBrightness); */
/*     for (size_t i = 0; i < 2; i++) { */
/*         for (int i = 0; i < context.numLEDs; i++) { */
/*             if (i % 2 == 0) { */
/*                 context.leds[i] = CRGB::Red; */
/*             } else { */
/*                 context.leds[i] = CRGB::White; */
/*             } */
/*         } */
/*         FastLED.show(); */
/*         delay(1000); */
/**/
/*         for (int i = 0; i < context.numLEDs; i++) { */
/*             context.leds[i] = CRGB::Black; */
/*         } */
/*         FastLED.show(); */
/*         delay(300); */
/*     } */
/* } */
/**/
/* void success(Context &context) { */
/*     FastLED.setBrightness(gContext.alertBrightness); */
/*     for (size_t i = 0; i < 2; i++) { */
/*         for (int i = 0; i < context.numLEDs; i++) { */
/*             context.leds[i] = CRGB::Green; */
/*         } */
/*         FastLED.show(); */
/*         delay(1000); */
/**/
/*         for (int i = 0; i < context.numLEDs; i++) { */
/*             context.leds[i] = CRGB::Black; */
/*         } */
/*         FastLED.show(); */
/*         delay(300); */
/*     } */
/* } */
/**/
/* typedef void (*SimplePatternList[])(Context &context); */
/* SimplePatternList gPatterns = { */
/*     christmas, christmas, christmas, rainbow, rainbowWithGlitter, */
/*     confetti,  sinelon,   juggle,    bpm}; */
/**/
