#include "main.h"

// int getBrightness(String command) { return gContext.brightness; }
// int setBrightness(String command) {
//     gContext.brightness = command.toInt();
//     return 1;
// }

// int getAlertBrightness(String command) { return gContext.alertBrightness; }
// int setAlertBrightness(String command) {
//     gContext.alertBrightness = command.toInt();
//     return 1;
// }

// int gotoNextPattern(String command) {
//     gContext.currentPatternNumber =
//         (gContext.currentPatternNumber + 1) % ARRAY_SIZE(gPatterns);
//     return 1;
// }

// int showError(String command) {
//     error(gContext);
//     return 1;
// }

// int showSuccess(String command) {
//     success(gContext);
//     return 1;
// }

void setup() {
    gContext.strip->begin();
    gContext.strip->show();

    // Particle.function("getBrightness", getBrightness);
    // Particle.function("setBrightness", setBrightness);
    // Particle.function("getAlertBrightness", getAlertBrightness);
    // Particle.function("setAlertBrightness", setAlertBrightness);
    // Particle.function("nextPattern", gotoNextPattern);
    // Particle.function("showError", showError);
    // Particle.function("showSuccess", showSuccess);
}

void loop() {
    gContext.strip->setBrightness(gContext.brightness);

    // Call the current pattern function once, updating the 'leds' array
    // gPatterns[gContext.currentPatternNumber](gContext);

    // EVERY_N_MILLISECONDS(20) { gContext.hue++; }
    // EVERY_N_SECONDS(10) {
    //     gContext.currentPatternNumber =
    //         (gContext.currentPatternNumber + 1) % ARRAY_SIZE(gPatterns);
    // }

    rainbow(20, gContext);
    addGlitter(80, gContext);

    gContext.iteration++;
}

void rainbow(uint8_t wait, Context &context) {
    uint16_t i, j;

    for (j = 0; j < 256; j++) {
        for (i = 0; i < context.strip->numPixels(); i++) {
            context.strip->setPixelColor(i, Wheel((i + j) & 255, context));
        }
        context.strip->show();
        delay(wait);
    }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos, Context &context) {
    if (WheelPos < 85) {
        return context.strip->Color(WheelPos * 3, 255 - WheelPos * 3, 0);
    } else if (WheelPos < 170) {
        WheelPos -= 85;
        return context.strip->Color(255 - WheelPos * 3, 0, WheelPos * 3);
    } else {
        WheelPos -= 170;
        return context.strip->Color(0, WheelPos * 3, 255 - WheelPos * 3);
    }
}
