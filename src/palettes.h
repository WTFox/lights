// There are several different palettes of colors demonstrated here.
//
// FastLED provides several 'preset' palettes: RainbowColors_p,
// RainbowStripeColors_p, OceanColors_p, CloudColors_p, LavaColors_p,
// ForestColors_p, and PartyColors_p.
//
// Additionally, you can manually define your own color palettes, or you can
// write code that creates color palettes on the fly.  All are shown here.

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

// extern CRGBPalette16 myChristmasPalette;
// extern const TProgmemPalette16 myChristmasPalette_p PROGMEM;
// const TProgmemPalette16 myChristmasPalette_p PROGMEM = {
//     CRGB::Red,   CRGB::Green, CRGB::Green, CRGB::Green,
//     CRGB::Green, CRGB::Green, CRGB::Green, CRGB::Green,
//     CRGB::Green, CRGB::Green, CRGB::Green, CRGB::Green,
//     CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black};

// extern CRGBPalette16 myRedWhiteBluePalette;
// extern const TProgmemPalette16 myRedWhiteBluePalette_p PROGMEM;
// const TProgmemPalette16 myRedWhiteBluePalette_p PROGMEM = {
//     CRGB::Red,  CRGB::Gray,  CRGB::Blue,  CRGB::Black, CRGB::Red, CRGB::Gray,
//     CRGB::Blue, CRGB::Black, CRGB::Red,   CRGB::Red,   CRGB::Gray,
//     CRGB::Gray, CRGB::Blue, CRGB::Blue,  CRGB::Black, CRGB::Black};
