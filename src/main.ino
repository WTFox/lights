#include "GlobalContext.h"
#include "main.h"
#include "neopixel.h"
#include "patterns/allPatterns.h"

#define NUM_LEDS 100
#define DATA_PIN D5
#define LED_TYPE WS2811

GlobalContext context = {
    .brightness = 150,
    .alertBrightness = 255,
    .currentPattern = 0,
    .strip = Adafruit_NeoPixel(NUM_LEDS, DATA_PIN, LED_TYPE),
};

typedef void (*PatternFunction)();

struct Pattern {
    void (*setupFunc)(GlobalContext &);
    void (*loopFunc)(GlobalContext &);
    String name;
};

Pattern patterns[] = {
    {twinkleSetup, twinkleLoop, "twinkle"},
    {fireplaceSetup, fireplaceLoop, "fireplace"},
};

unsigned long lastPatternChange = 0;
const unsigned long patternDuration = 5000; // 5 seconds
int currentPatternIndex = 0;

void setup() {
    Particle.function("getBrightness", getBrightness);
    Particle.function("setBrightness", setBrightness);
    Particle.function("getAlertBrightness", getAlertBrightness);
    Particle.function("setAlertBrightness", setAlertBrightness);
    Particle.function("nextPattern", gotoNextPattern);

    context.strip.begin();
    context.strip.show();
    patterns[currentPatternIndex].setupFunc(context);
}

void loop() {
    context.strip.setBrightness(context.brightness);
    patterns[currentPatternIndex].loopFunc(context);

    if (millis() - lastPatternChange >= patternDuration) {
        currentPatternIndex = (currentPatternIndex + 1) % ARRAY_SIZE(patterns);
        patterns[currentPatternIndex].setupFunc(context);
        lastPatternChange = millis();
    }
}

int gotoNextPattern(String command) { return 1; }

int getBrightness(String command) { return 1; }
int setBrightness(String command) { return 1; }

int getAlertBrightness(String command) { return 1; }
int setAlertBrightness(String command) { return 1; }

int showError(String command) { return 1; }
int showSuccess(String command) { return 1; }
