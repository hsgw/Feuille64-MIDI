#pragma once

#include "matrix.h"

// raw is the current key state
// on entry cooked is the previous debounced state
// on exit cooked is the current debounced state
// changed is true if raw has changed since the last call
void debounce(matrix_row_t raw[], matrix_row_t cooked[], uint8_t num_rows, bool changed);

void debounce_init(void);

void debounce_update(void);
bool debounce_is_active(uint8_t row, uint8_t col);
void debounce_set_active(uint8_t row, uint8_t col);
