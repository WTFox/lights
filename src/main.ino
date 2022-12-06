#include "../lib/FastLED/src/FastLED.h"
FASTLED_USING_NAMESPACE;

#define PARTICLE_NO_ARDUINO_COMPATIBILITY 1
#include "Particle.h"
#define FL_PROGMEM
#include "palettes.h"

#define NUM_LEDS 95
#define DATA_PIN D5
#define LED_TYPE WS2811
CRGB leds[NUM_LEDS];

#define BRIGHTNESS 200
#define FRAMES_PER_SECOND 60

uint8_t gCurrentPatternNumber = 0; // Index number of which pattern is
uint8_t gHue = 0;  // rotating "base color" used by many of the patterns
uint8_t iteration; // loop cycles

#define ARRAY_SIZE(A) (sizeof(A) / sizeof((A)[0]))
typedef void (*SimplePatternList[])();
SimplePatternList gPatterns = {christmas, rainbow,  rainbowWithGlitter,
                               confetti,  sinelon,  juggle,
                               bpm,       christmas};

const uint8_t numLEDs = ARRAY_SIZE(leds);

int setBrightness(String command) {
    FastLED.setBrightness(command.toInt());
    return 1;
}

int getBrightness(String command) { return FastLED.getBrightness(); }

int gotoNextPattern(String command) {
    nextPattern();
    return 1;
}

void setup() {
    delay(3000);
    FastLED.addLeds<LED_TYPE, DATA_PIN>(leds, NUM_LEDS)
        .setCorrection(TypicalLEDStrip);
    FastLED.setBrightness(BRIGHTNESS);

    Particle.function("setBrightness", setBrightness);
    Particle.function("getBrightness", getBrightness);
    Particle.function("nextPattern", gotoNextPattern);

    iteration = 0;
}

void loop() {
    // Call the current pattern function once, updating the 'leds' array
    gPatterns[gCurrentPatternNumber]();
    FastLED.show();

    // insert a delay to keep the framerate modest
    FastLED.delay(1000 / FRAMES_PER_SECOND);

    EVERY_N_MILLISECONDS(20) { gHue++; }
    EVERY_N_SECONDS(10) { nextPattern(); }
    iteration++;
}

void nextPattern() {
    gCurrentPatternNumber = (gCurrentPatternNumber + 1) % ARRAY_SIZE(gPatterns);
}

void FillLEDsFromPaletteColors(CRGBPalette16 currentPalette) {
    uint8_t colorIndex = iteration;
    for (int i = 0; i < NUM_LEDS; ++i) {
        leds[i] = ColorFromPalette(currentPalette, colorIndex,
                                   (uint8_t)BRIGHTNESS, LINEARBLEND);
        colorIndex += 3;
    }
}

void christmas() {
    FillLEDsFromPaletteColors(myChristmasPalette_p);
    addGlitter(30);
}

void rainbow() { fill_rainbow(leds, numLEDs, gHue, 7); }

void rainbowWithGlitter() {
    rainbow();
    addGlitter(80);
}

void addGlitter(fract8 chanceOfGlitter) {
    if (random8() < chanceOfGlitter) {
        leds[random16(numLEDs)] += CRGB::Gray; // White is too bright
    }
}

void confetti() {
    // random colored speckles that blink in and fade smoothly
    fadeToBlackBy(leds, numLEDs, 10);
    int pos = random16(numLEDs);
    leds[pos] += CHSV(gHue + random8(64), 200, 255);
}

void sinelon() {
    // a colored dot sweeping back and forth, with fading trails
    fadeToBlackBy(leds, numLEDs, 20);
    int pos = beatsin16(13, 0, numLEDs - 1);
    leds[pos] += CHSV(gHue, 255, 192);
}

void bpm() {
    // colored stripes pulsing at a defined Beats-Per-Minute (BPM)
    uint8_t BeatsPerMinute = 62;
    CRGBPalette16 palette = PartyColors_p;
    uint8_t beat = beatsin8(BeatsPerMinute, 64, 255);
    for (int i = 0; i < numLEDs; i++) { // 9948
        leds[i] =
            ColorFromPalette(palette, gHue + (i * 2), beat - gHue + (i * 10));
    }
}

void juggle() {
    // eight colored dots, weaving in and out of sync with each other
    fadeToBlackBy(leds, numLEDs, 20);
    uint8_t dothue = 0;
    for (int i = 0; i < 8; i++) {
        leds[beatsin16(i + 7, 0, numLEDs - 1)] |= CHSV(dothue, 200, 255);
        dothue += 32;
    }
}
