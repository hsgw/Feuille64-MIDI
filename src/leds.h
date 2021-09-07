#pragma once

#include <stdint.h>

void leds_init(void);
void leds_update(void);

void leds_set(uint8_t row, uint8_t col, uint8_t brightness);
void leds_set_all(uint8_t brightness);