/*   Copyright 2021 Takuya Urakawa (hsgw), QMK
 *
 *   This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 2 of the License, or
 *   (at your option) any later version.

 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

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
