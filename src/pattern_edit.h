#pragma once

#include <stdint.h>

void pattern_edit_step_begin(uint8_t no);
void pattern_edit_step_begin_current(void);
void pattern_edit_step_step(uint8_t row, uint8_t col);

void pattern_edit_velocity_begin(uint8_t pattern);
void pattern_edit_velocity_begin_current(void);
void pattern_edit_velocity_set_velocity(uint8_t step, uint8_t velocity);
void pattern_edit_velocity_toggle_enable(uint8_t step);
void pattern_edit_velocity_toggle_enable(uint8_t length);