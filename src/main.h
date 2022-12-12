#include "neopixel.h"
#include "utils.h"

#define NUM_LEDS 50
#define DATA_PIN D5
#define LED_TYPE WS2811

class Context {
  public:
    uint8_t numLEDs;
    uint8_t brightness = 200;
    uint8_t alertBrightness = 255;
    uint8_t hue = 0;
    uint8_t iteration = 0;
    uint8_t currentPatternNumber = 0;
    Adafruit_NeoPixel *strip =
        new Adafruit_NeoPixel(NUM_LEDS, DATA_PIN, LED_TYPE);
    void setHue(uint8_t hue) { this->hue = hue; }
    void inrecementIteration() { this->iteration++; }
    void setBrightness(uint8_t brightness) { this->brightness = brightness; }
};

Context *gContext = new Context();

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t wheel(byte WheelPos, Context *context) {
    if (WheelPos < 85) {
        return context->strip->Color(WheelPos * 3, 255 - WheelPos * 3, 0);
    } else if (WheelPos < 170) {
        WheelPos -= 85;
        return context->strip->Color(255 - WheelPos * 3, 0, WheelPos * 3);
    } else {
        WheelPos -= 170;
        return context->strip->Color(0, WheelPos * 3, 255 - WheelPos * 3);
    }
}
void addGlitter(uint8_t chanceOfGlitter, Context *context) {
    if (random8(chanceOfGlitter)) {
        context->strip->setPixelColor(random16(0, context->strip->numPixels()),
                                      context->strip->Color(255, 255, 255));
    }
    gContext->strip->show();
}

void rainbow(Context *context) {
    uint16_t i, j;
    for (j = 0; j < 256; j++) {
        for (i = 0; i < context->strip->numPixels(); i++) {
            context->strip->setPixelColor(
                i, wheel(((i + j + context->iteration) & 255), context));
        }
    }
    gContext->strip->show();
}

void rainbowWithGlitter(Context *context) {
    rainbow(context);
    addGlitter(10, context);
}

void error(Context *context) {
    context->strip->setBrightness(gContext->alertBrightness);

    for (int i = 0; i < context->numLEDs; i++) {
        context->strip->setPixelColor(i, 255, 0, 0);
    }
    context->strip->show();
    delay(1000);

    for (int i = 0; i < context->numLEDs; i++) {
        context->strip->setPixelColor(i, 0, 0, 0);
    }
    context->strip->show();
    delay(300);
}

void success(Context *context) {
    context->strip->setBrightness(gContext->alertBrightness);
    for (int i = 0; i < context->numLEDs; i++) {
        context->strip->setPixelColor(i, Adafruit_NeoPixel::Color(0, 255, 0));
    }
    context->strip->show();
    delay(1000);

    for (int i = 0; i < context->numLEDs; i++) {
        context->strip->setPixelColor(i, Adafruit_NeoPixel::Color(0, 0, 0));
    }
    context->strip->show();
    delay(300);
}

typedef void (*Pattern)(Context *context);
Pattern gPatterns[] = {rainbow, rainbowWithGlitter};
