uint8_t random8(uint8_t min, uint8_t max) {
    return min + (rand() % (int)(max - min + 1));
}

uint16_t random16(uint16_t min, uint16_t max) {
    return min + (rand() % (int)(max - min + 1));
}
