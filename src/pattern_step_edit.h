#pragma once

#include <stdint.h>

void pattern_step_edit_begin(uint8_t no);
void pattern_step_edit_begin_current(void);
void pattern_step_edit_step(uint8_t row, uint8_t col);