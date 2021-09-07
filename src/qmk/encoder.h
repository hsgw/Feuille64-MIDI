#pragma once

#include <stdbool.h>
#include <stdint.h>

void encoder_init(void);
void encoder_update(void);

void encoder_changed(uint8_t index, bool clockwise);
