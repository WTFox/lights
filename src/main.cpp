/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#include "Particle.h"
#line 1 "/Users/anthonyfox/dev/lights/src/main.ino"
#include "../lib/FastLED/src/FastLED.h"
int setBrightness(String command);
int getBrightness(String command);
int gotoNextPattern(String command);
int showError(String command);
int showSuccess(String command);
void setup();
void loop();
#line 2 "/Users/anthonyfox/dev/lights/src/main.ino"
FASTLED_USING_NAMESPACE;

#include "main.h"

int setBrightness(String command) {
    FastLED.setBrightness(command.toInt());
    return 1;
}

int getBrightness(String command) { return FastLED.getBrightness(); }

int gotoNextPattern(String command) {
    gContext.currentPatternNumber =
        (gContext.currentPatternNumber + 1) % ARRAY_SIZE(gPatterns);
    return 1;
}

int showError(String command) {
    error(gContext);
    return 1;
}

int showSuccess(String command) {
    success(gContext);
    return 1;
}

void setup() {
    delay(3000);
    FastLED.addLeds<LED_TYPE, DATA_PIN>(gContext.leds, NUM_LEDS)
        .setCorrection(TypicalLEDStrip);
    FastLED.setBrightness(gContext.brightness);

    Particle.function("setBrightness", setBrightness);
    Particle.function("getBrightness", getBrightness);
    Particle.function("nextPattern", gotoNextPattern);
    Particle.function("showError", showError);
    Particle.function("showSuccess", showSuccess);
}

void loop() {
    // Call the current pattern function once, updating the 'leds' array
    gPatterns[gContext.currentPatternNumber](gContext);

    FastLED.show();
    // insert a delay to keep the framerate modest
    FastLED.delay(1000 / FRAMES_PER_SECOND);

    EVERY_N_MILLISECONDS(20) { gContext.hue++; }
    EVERY_N_SECONDS(10) {
        gContext.currentPatternNumber =
            (gContext.currentPatternNumber + 1) % ARRAY_SIZE(gPatterns);
    }
    gContext.iteration++;
}
