#include "main_ino.h"

#define PIXEL_TYPE WS2812B
#if (PLATFORM_ID == 32)
// Photon2
#define PIXEL_PIN SPI1
#else
#define PIXEL_PIN D5
#endif

GlobalContext context = {
    .brightness = 150,
    .nightTimeBrightness = 25,
    .alertBrightness = 255,
    .currentPattern = 0,
    .patternDurationInSeconds = 15 * 60 * 1000,
    .lastPatternChange = 0,
    .iteration = 0,
    .strip = Adafruit_NeoPixel(NUM_LEDS, PIXEL_PIN, PIXEL_TYPE),
    .cyclePatterns = false,
    .nightModeActive = false,
    .currentPatternName = "",
};

void setup() {
    Time.zone(-7);

    // published functions
    Particle.function("getBrightness", getBrightness);
    Particle.function("setBrightness", setBrightness);
    Particle.function("getNightTimeBrightness", getNightTimeBrightness);
    Particle.function("setNightTimeBrightness", setNightTimeBrightness);
    Particle.function("nextPattern", gotoNextPattern);
    Particle.function("setPatternDurationMinutes", setPatternDurationMinutes);
    Particle.function("toggleCyclingPatterns", toggleCyclingPatterns);
    Particle.function("triggerAlertEvent", triggerAlertEvent);

    // events subscribed to
    Particle.subscribe("alert", handleEvent);

    // published variables
    Particle.variable("currentPattern", context.currentPatternName);

    // rest of setup
    context.strip.begin();
    context.strip.show();
    context.strip.setBrightness(context.brightness);
    patterns[context.currentPattern].setupFunc(
        context, patterns[context.currentPattern].args);
}

void loop() {
    handleEvents(context);
    handleNightMode(context);

    patterns[context.currentPattern].loopFunc(
        context, patterns[context.currentPattern].args);
    if (context.cyclePatterns) {
        if (millis() - context.lastPatternChange >=
            static_cast<unsigned long>(context.patternDurationInSeconds)) {
            gotoNextPattern("");
            context.lastPatternChange = millis();
        }
    }

    context.currentPatternName = patterns[context.currentPattern].name;
    context.iteration++;
}

void handleNightMode(GlobalContext &context) {
    String nightTimePattern = "nightSky";
    if (Time.hour() >= 22 && !context.nightModeActive) {
        context.nightModeActive = true;
        context.strip.setBrightness(context.nightTimeBrightness);
        setPattern(context, lookupPatternByName(nightTimePattern));

    } else if (Time.hour() < 7 && !context.nightModeActive) {
        context.nightModeActive = true;
        context.strip.setBrightness(context.nightTimeBrightness);
        setPattern(context, lookupPatternByName(nightTimePattern));

    } else if (Time.hour() >= 7 && context.nightModeActive) {
        context.nightModeActive = false;
        context.strip.setBrightness(context.brightness);
        setPattern(context, context.currentPattern);

    } else {
        context.strip.setBrightness(context.brightness);
    }
}

void handleEvents(GlobalContext &context) {
    switch (context.event_type) {
    case Events::Type::Alert:
        handleAlertEvent(context);
        return;
    default:
        break;
    }
}

void alertLoop(GlobalContext &context) {
    context.strip.setBrightness(context.alertBrightness);
    for (int i = 0; i < NUM_LEDS; i++) {
        // rgb but it's actually grb
        context.strip.setPixelColor(i, 0x00ff00);
    }
    context.strip.show();
    delay(500);
    for (int i = 0; i < NUM_LEDS; i++) {
        context.strip.setPixelColor(i, 0x000000);
    }
    context.strip.show();
    delay(500);
}

void handleAlertEvent(GlobalContext &context) {
    unsigned long alertDuration = 5000; // 5 seconds
    if (millis() - context.lastEventStart < alertDuration) {
        alertLoop(context);
    } else {
        context.strip.setBrightness(context.brightness);
        context.event_type = Events::Type::None;
    }
}

// region Particle functions
int getBrightness(String command) { return context.brightness; }
int setBrightness(String command) {
    context.brightness = command.toInt();
    return context.brightness;
}

int getNightTimeBrightness(String command) {
    return context.nightTimeBrightness;
}

int setNightTimeBrightness(String command) {
    context.nightTimeBrightness = command.toInt();
    return context.nightTimeBrightness;
}

int setPatternDurationMinutes(String command) {
    context.patternDurationInSeconds = command.toInt() * 60 * 1000;
    return context.patternDurationInSeconds / 1000 / 60;
}

int toggleCyclingPatterns(String command) {
    context.cyclePatterns = !context.cyclePatterns;
    return 1;
}

int triggerAlertEvent(String command) {
    context.event_type = Events::Type::Alert;
    context.lastEventStart = millis();
    return 1;
}

void handleEvent(const char *event, const char *data) {
    if (strcmp(event, "alert") == 0) {
        context.event_type = Events::Type::Alert;
        context.lastEventStart = millis();
    }
}

int gotoNextPattern(String command) {
    context.currentPattern =
        (context.currentPattern + 1) % ARRAY_SIZE(patterns);
    patterns[context.currentPattern].setupFunc(
        context, patterns[context.currentPattern].args);
    return 1;
}
// endregion

uint8_t randomInt() { return rand() % 101; }
uint16_t random16(uint16_t max) { return rand() % max; }
