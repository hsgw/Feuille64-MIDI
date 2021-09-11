#pragma once

#include <stdint.h>
#include <stdbool.h>

void pattern_velocity_edit_begin(uint8_t pattern);
void pattern_velocity_edit_begin_current(void);
void pattern_velocity_edit_set_velocity(uint8_t step, uint8_t velocity);
void pattern_velocity_edit_toggle_enable(uint8_t step);
