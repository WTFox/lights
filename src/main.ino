#include "../lib/FastLED/src/FastLED.h"
FASTLED_USING_NAMESPACE;

#define PARTICLE_NO_ARDUINO_COMPATIBILITY 1
#include "Particle.h"
#define FL_PROGMEM

#define NUM_LEDS 95
#define DATA_PIN D5
#define LED_TYPE WS2811
CRGB leds[NUM_LEDS];

#define BRIGHTNESS 200
#define FRAMES_PER_SECOND 60

#define ARRAY_SIZE(A) (sizeof(A) / sizeof((A)[0]))

extern CRGBPalette16 myRedWhiteBluePalette;
extern const TProgmemPalette16 myRedWhiteBluePalette_p PROGMEM;

extern CRGBPalette16 myChristmasPalette;
extern const TProgmemPalette16 myChristmasPalette_p PROGMEM;

uint8_t iteration;

typedef void (*SimplePatternList[])();
SimplePatternList gPatterns = {christmas, rainbow,  rainbowWithGlitter,
                               confetti,  sinelon,  juggle,
                               bpm,       christmas};

uint8_t gCurrentPatternNumber = 0; // Index number of which pattern is
uint8_t gHue = 0;                  // rotating "base color" used by many of the

void setup() {
    delay(3000);
    FastLED.addLeds<LED_TYPE, DATA_PIN>(leds, NUM_LEDS)
        .setCorrection(TypicalLEDStrip);
    FastLED.setBrightness(BRIGHTNESS);
    iteration = 0;
}

void loop() {
    // Call the current pattern function once, updating the 'leds' array
    gPatterns[gCurrentPatternNumber]();
    FastLED.show();

    // insert a delay to keep the framerate modest
    FastLED.delay(1000 / FRAMES_PER_SECOND);

    // do some periodic updates
    EVERY_N_MILLISECONDS(20) {
        gHue++;
    } // slowly cycle the "base color" through the rainbow
    EVERY_N_SECONDS(10) { nextPattern(); } // change patterns periodically
    iteration++;
}

void nextPattern() {
    gCurrentPatternNumber = (gCurrentPatternNumber + 1) % ARRAY_SIZE(gPatterns);
}

void christmas() {
    FillLEDsFromPaletteColors(myChristmasPalette_p);
    addGlitter(30);
}

void rainbow() { fill_rainbow(leds, NUM_LEDS, gHue, 7); }

void rainbowWithGlitter() {
    rainbow();
    addGlitter(80);
}

void addGlitter(fract8 chanceOfGlitter) {
    if (random8() < chanceOfGlitter) {
        leds[random16(NUM_LEDS)] += CRGB::Gray; // White is too bright
    }
}

void confetti() {
    // random colored speckles that blink in and fade smoothly
    fadeToBlackBy(leds, NUM_LEDS, 10);
    int pos = random16(NUM_LEDS);
    leds[pos] += CHSV(gHue + random8(64), 200, 255);
}

void sinelon() {
    // a colored dot sweeping back and forth, with fading trails
    fadeToBlackBy(leds, NUM_LEDS, 20);
    int pos = beatsin16(13, 0, NUM_LEDS - 1);
    leds[pos] += CHSV(gHue, 255, 192);
}

void bpm() {
    // colored stripes pulsing at a defined Beats-Per-Minute (BPM)
    uint8_t BeatsPerMinute = 62;
    CRGBPalette16 palette = PartyColors_p;
    uint8_t beat = beatsin8(BeatsPerMinute, 64, 255);
    for (int i = 0; i < NUM_LEDS; i++) { // 9948
        leds[i] =
            ColorFromPalette(palette, gHue + (i * 2), beat - gHue + (i * 10));
    }
}

void juggle() {
    // eight colored dots, weaving in and out of sync with each other
    fadeToBlackBy(leds, NUM_LEDS, 20);
    uint8_t dothue = 0;
    for (int i = 0; i < 8; i++) {
        leds[beatsin16(i + 7, 0, NUM_LEDS - 1)] |= CHSV(dothue, 200, 255);
        dothue += 32;
    }
}

void FillLEDsFromPaletteColors(CRGBPalette16 currentPalette) {
    uint8_t colorIndex = iteration;
    for (int i = 0; i < NUM_LEDS; ++i) {
        leds[i] = ColorFromPalette(currentPalette, colorIndex,
                                   (uint8_t)BRIGHTNESS, LINEARBLEND);
        colorIndex += 3;
    }
}

const TProgmemPalette16 myChristmasPalette_p PROGMEM = {
    CRGB::Red,   CRGB::Green, CRGB::Green, CRGB::Green,
    CRGB::Green, CRGB::Green, CRGB::Green, CRGB::Green,
    CRGB::Green, CRGB::Green, CRGB::Green, CRGB::Green,
    CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black};

const TProgmemPalette16 myRedWhiteBluePalette_p PROGMEM = {
    CRGB::Red,  CRGB::Gray,  CRGB::Blue,  CRGB::Black, CRGB::Red,  CRGB::Gray,
    CRGB::Blue, CRGB::Black, CRGB::Red,   CRGB::Red,   CRGB::Gray, CRGB::Gray,
    CRGB::Blue, CRGB::Blue,  CRGB::Black, CRGB::Black};

// There are several different palettes of colors demonstrated here.
//
// FastLED provides several 'preset' palettes: RainbowColors_p,
// RainbowStripeColors_p, OceanColors_p, CloudColors_p, LavaColors_p,
// ForestColors_p, and PartyColors_p.
//
// Additionally, you can manually define your own color palettes, or you can
// write code that creates color palettes on the fly.  All are shown here.

// void ChangePalettePeriodically() {
//     uint8_t secondHand = (millis() / 1000) % 60;
//     static uint8_t lastSecond = 99;

//     if (lastSecond != secondHand) {
//         lastSecond = secondHand;
//         if (secondHand == 0) {
//             // currentPalette = RainbowColors_p;
//             currentPalette = myChristmasPalette_p;
//             currentBlending = LINEARBLEND;
//         }
//         if (secondHand == 10) {
//             // currentPalette = RainbowStripeColors_p;
//             currentPalette = myChristmasPalette_p;
//             currentBlending = NOBLEND;
//         }
//         if (secondHand == 15) {
//             currentPalette = RainbowStripeColors_p;
//             currentBlending = LINEARBLEND;
//         }
//         if (secondHand == 20) {
//             SetupPurpleAndGreenPalette();
//             currentBlending = LINEARBLEND;
//         }
//         if (secondHand == 25) {
//             SetupTotallyRandomPalette();
//             currentBlending = LINEARBLEND;
//         }
//         if (secondHand == 30) {
//             SetupBlackAndWhiteStripedPalette();
//             currentBlending = NOBLEND;
//         }
//         if (secondHand == 35) {
//             SetupBlackAndWhiteStripedPalette();
//             currentBlending = LINEARBLEND;
//         }
//         if (secondHand == 40) {
//             currentPalette = CloudColors_p;
//             currentBlending = LINEARBLEND;
//         }
//         if (secondHand == 45) {
//             currentPalette = PartyColors_p;
//             currentBlending = LINEARBLEND;
//         }
//         if (secondHand == 50) {
//             currentPalette = myRedWhiteBluePalette_p;
//             currentBlending = NOBLEND;
//         }
//         if (secondHand == 55) {
//             currentPalette = myRedWhiteBluePalette_p;
//             currentBlending = LINEARBLEND;
//         }
//     }
// }
//
//
// Additional notes on FastLED compact palettes:
//
// Normally, in computer graphics, the palette (or "color lookup table")
// has 256 entries, each containing a specific 24-bit RGB color.  You can then
// index into the color palette using a simple 8-bit (one byte) value.
// A 256-entry color palette takes up 768 bytes of RAM, which on Arduino
// is quite possibly "too many" bytes.
//
// FastLED does offer traditional 256-element palettes, for setups that
// can afford the 768-byte cost in RAM.
//
// However, FastLED also offers a compact alternative.  FastLED offers
// palettes that store 16 distinct entries, but can be accessed AS IF
// they actually have 256 entries; this is accomplished by interpolating
// between the 16 explicit entries to create fifteen intermediate palette
// entries between each pair.
//
// So for example, if you set the first two explicit entries of a compact
// palette to Green (0,255,0) and Blue (0,0,255), and then retrieved
// the first sixteen entries from the virtual palette (of 256), you'd get
// Green, followed by a smooth gradient from green-to-blue, and then Blue.
