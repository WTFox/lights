#include "../lib/FastLED/src/FastLED.h"
FASTLED_USING_NAMESPACE;

#include "main.h"

int getBrightness(String command) { return gContext.brightness; }
int setBrightness(String command) {
    gContext.brightness = command.toInt();
    return 1;
}

int getAlertBrightness(String command) { return gContext.alertBrightness; }
int setAlertBrightness(String command) {
    gContext.alertBrightness = command.toInt();
    return 1;
}

int getFPS(String command) { return gContext.fps; }
int setFPS(String command) {
    gContext.fps = command.toInt();
    return 1;
}

int gotoNextPattern(String command) {
    gContext.currentPatternNumber =
        (gContext.currentPatternNumber + 1) % ARRAY_SIZE(gPatterns);
    return 1;
}

int setDelay(String command) {
    gContext.fps = command.toInt();
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

    Particle.function("getBrightness", getBrightness);
    Particle.function("setBrightness", setBrightness);
    Particle.function("getAlertBrightness", getAlertBrightness);
    Particle.function("setAlertBrightness", setAlertBrightness);
    Particle.function("getFPS", getFPS);
    Particle.function("setFPS", setFPS);
    Particle.function("setDelay", setDelay);
    Particle.function("nextPattern", gotoNextPattern);
    Particle.function("showError", showError);
    Particle.function("showSuccess", showSuccess);
}

void loop() {
    FastLED.setBrightness(gContext.brightness);

    // Call the current pattern function once, updating the 'leds' array
    gPatterns[gContext.currentPatternNumber](gContext);

    // insert a delay to keep the framerate modest
    FastLED.delay(1000 / gContext.fps);

    EVERY_N_MILLISECONDS(20) { gContext.hue++; }
    EVERY_N_SECONDS(10) {
        gContext.currentPatternNumber =
            (gContext.currentPatternNumber + 1) % ARRAY_SIZE(gPatterns);
    }

    FastLED.show();
    gContext.iteration++;
}
