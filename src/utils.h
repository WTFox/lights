uint16_t random16(uint16_t min, uint16_t max) {
    return min + (rand() % (int)(max - min + 1));
}

uint8_t random8(uint8_t chance) { return (rand() % 100) < chance; }


void EVERY_N_MILLISECONDS(uint16_t ms, void (*callback)()) {
    static uint32_t lastRun = 0;
    if (millis() - lastRun > ms) {
        lastRun = millis();
        callback();
    }
}

void EVERY_N_SECONDS(uint16_t seconds, void (*callback)()) {
    EVERY_N_MILLISECONDS(seconds * 1000, callback);
}
