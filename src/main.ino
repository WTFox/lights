#include "main_ino.h"

#define PIXEL_TYPE WS2812B
#if (PLATFORM_ID == PLATFORM_P2)
#define PIXEL_PIN SPI1
#else
#define PIXEL_PIN D5
#endif

GlobalContext context = {
    .brightness = 150,
    .nightTimeBrightness = 15,
    .alertBrightness = 255,
    .currentPattern = 0,
    .patternDurationInSeconds = 15 * 60 * 1000,
    .lastPatternChange = 0,
    .iteration = 0,
    .strip = Adafruit_NeoPixel(NUM_LEDS, PIXEL_PIN, PIXEL_TYPE),
    .cyclePatterns = true,
    .nightModeActive = false,
    .currentPatternName = "",
    .currentTagFilter = "autumn",
    .alertColor = 0xff0000,
    .nightTimeStart = 22,
    .nightTimeEnd = 8,
};

String oldFilterTag = "";

void setup() {
    Time.zone(-7);

    // published functions
    Particle.function("getBrightness", getBrightness);
    Particle.function("setBrightness", setBrightness);
    Particle.function("getNightTimeBrightness", getNightTimeBrightness);
    Particle.function("setNightTimeBrightness", setNightTimeBrightness);
    Particle.function("setCurrentTagFilter", setCurrentTagFilter);
    Particle.function("nextPattern", gotoNextPattern);
    Particle.function("setPatternDurationMinutes", setPatternDurationMinutes);
    Particle.function("toggleCyclingPatterns", toggleCyclingPatterns);
    Particle.function("triggerAlertEvent", triggerAlertEvent);

    // events subscribed to
    Particle.subscribe("alert", handleEvent);
    Particle.subscribe("setPatternTag", handleEvent);

    // published variables
    Particle.variable("currentPatternName", context.currentPatternName);
    Particle.variable("currentTagFilter", context.currentTagFilter);

    // rest of setup
    context.strip.begin();
    context.strip.show();
    context.strip.setBrightness(context.brightness);
    patterns[context.currentPattern].setupFunc(
        context, patterns[context.currentPattern].args);
}

void loop() {
    if (context.event_type != Events::Type::None) {
        handleEvents(context);
        return;
    }

    handleNightMode(context);

    int brightness =
        isNightTime(context) ? context.nightTimeBrightness : context.brightness;
    context.strip.setBrightness(brightness);

    std::vector<Pattern> filtered_patterns =
        filterPatternsByTag(patterns, context.currentTagFilter);

    filtered_patterns[context.currentPattern].loopFunc(
        context, filtered_patterns[context.currentPattern].args);

    if (context.cyclePatterns) {
        if (millis() - context.lastPatternChange >=
            static_cast<unsigned long>(context.patternDurationInSeconds)) {
            gotoNextPattern("");
            context.lastPatternChange = millis();
        }
    }

    context.currentPatternName = filtered_patterns[context.currentPattern].name;
    context.iteration++;
}

void handleNightMode(GlobalContext &context) {
    if (isNightTime(context) && !context.nightModeActive) {
        context.nightModeActive = true;
        oldFilterTag = context.currentTagFilter;
        context.currentTagFilter = "night";
        setPattern(context, 0);
    } else if (!isNightTime(context) && context.nightModeActive) {
        context.nightModeActive = false;
        context.currentTagFilter = oldFilterTag;
        setPattern(context, 0);
    }
}

void alertLoop(GlobalContext &context) {
    context.strip.setBrightness(context.alertBrightness);

    uint8_t r = (context.alertColor >> 16) & 0xff;
    uint8_t g = (context.alertColor >> 8) & 0xff;
    uint8_t b = context.alertColor & 0xff;

    for (int i = 0; i < NUM_LEDS; i++) {
        context.strip.setPixelColor(i, g, r, b);
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
        return;
    }

    context.event_type = Events::Type::None;
    return;
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

    if (command.length() > 0) {
        context.alertColor = strtoul(command.c_str(), NULL, 16);
    } else {
        context.alertColor = 0xff0000;
    }

    return 1;
}

void handleEvent(const char *event, const char *data) {

    if (strcmp(event, "alert") == 0) {
        if (isNightTime(context)) {
            // we don't want to alert at night time
            return;
        }

        context.event_type = Events::Type::Alert;
        context.lastEventStart = millis();
        if (data != NULL) {
            context.alertColor = strtoul(data, NULL, 16);
        } else {
            context.alertColor = 0xff0000;
        }
    } else if (strcmp(event, "setPatternTag") == 0) {
        context.currentTagFilter = data;
        setPattern(context, 0);
    }

    return;
}

int gotoNextPattern(String command) {
    std::vector<Pattern> filtered_patterns =
        filterPatternsByTag(patterns, context.currentTagFilter);

    context.currentPattern =
        (context.currentPattern + 1) % filtered_patterns.size();

    patterns[context.currentPattern].setupFunc(
        context, filtered_patterns[context.currentPattern].args);

    return 1;
}

int setCurrentTagFilter(String command) {
    context.currentTagFilter = command;
    return 1;
}
// endregion

bool isNightTime(GlobalContext &context) {
    return (Time.hour() >= context.nightTimeStart ||
            Time.hour() < context.nightTimeEnd);
}

uint8_t randomInt() { return rand() % 101; }
uint16_t random16(uint16_t max) { return rand() % max; }
