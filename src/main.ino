#include "main.h"

int getBrightness(String command) { return gContext->brightness; }
int setBrightness(String command) {
    gContext->brightness = command.toInt();
    return 1;
}

int getAlertBrightness(String command) { return gContext->alertBrightness; }
int setAlertBrightness(String command) {
    gContext->alertBrightness = command.toInt();
    return 1;
}

int gotoNextPattern(String command) {
    gContext->currentPatternNumber =
        (gContext->currentPatternNumber + 1) % ARRAY_SIZE(gPatterns);
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
    gContext->strip->begin();
    gContext->strip->show();

    Particle.function("getBrightness", getBrightness);
    Particle.function("setBrightness", setBrightness);
    Particle.function("getAlertBrightness", getAlertBrightness);
    Particle.function("setAlertBrightness", setAlertBrightness);
    Particle.function("nextPattern", gotoNextPattern);
    Particle.function("showError", showError);
    Particle.function("showSuccess", showSuccess);
}

// todo error and success not working
void loop() {
    gContext->strip->setBrightness(gContext->brightness);
    gPatterns[gContext->currentPatternNumber](gContext);

    EVERY_N_SECONDS(10, []() {
        gContext->currentPatternNumber =
            (gContext->currentPatternNumber + 1) % ARRAY_SIZE(gPatterns);
    });

    gContext->strip->show();
    gContext->iteration++;
}
