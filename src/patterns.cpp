#include "patterns.h"

Color::Color() : r(0), g(0), b(0) {}

Color::Color(uint32_t value)
    : r((value >> 16) & 0xFF), g((value >> 8) & 0xFF), b(value & 0xFF) {}
