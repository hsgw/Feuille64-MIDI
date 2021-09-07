/*
Copyright 2012-2018 Jun Wako, Jack Humbert, Yiancar

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include "matrix.h"
#include "gpio.h"
#include "debounce.h"

#include <stdbool.h>
#include <stdint.h>
#include <util/atomic.h>

static const pin_t row_pins[MATRIX_ROWS] = MATRIX_ROW_PINS;
static const pin_t col_pins[MATRIX_COLS] = MATRIX_COL_PINS;

static const uint8_t col_order[MATRIX_COLS] = COL_ORDER;

/* matrix state(1:on, 0:off) */
matrix_row_t matrix[MATRIX_ROWS];  // debounced values

// helper functions
void matrix_output_select_delay(void) { __builtin_avr_delay_cycles(2); }
void matrix_output_unselect_delay(void) { _delay_us(20); }

static inline void setPinOutput_writeLow(pin_t pin) {
    ATOMIC_BLOCK(ATOMIC_FORCEON) {
        setPinOutput(pin);
        writePinLow(pin);
    }
}

static inline void setPinInputHigh_atomic(pin_t pin) {
    ATOMIC_BLOCK(ATOMIC_FORCEON) { setPinInputHigh(pin); }
}

// matrix code
static void select_row(uint8_t row) { setPinOutput_writeLow(row_pins[row]); }

static void unselect_row(uint8_t row) { setPinInputHigh_atomic(row_pins[row]); }

static void unselect_rows(void) {
    for (uint8_t x = 0; x < MATRIX_ROWS; x++) {
        setPinInputHigh_atomic(row_pins[x]);
    }
}

// This code is closely related to the hardware.
static inline matrix_row_t read_cols_on_row(uint8_t current_row) {
    // Select row
    select_row(current_row);
    matrix_output_select_delay();

    // Compress the raw data to the size of matrix_row_t.
    // order is COL_ORDER
    matrix_row_t current_row_value = ~(((PINF & 0b00000010) >> 1) + ((PINF & 0b011110000) >> 3) + ((PINB & 0b00001110) << 4));

    // Unselect row
    unselect_row(current_row);
    matrix_output_unselect_delay();  // wait for all Col signals to go HIGH

    return current_row_value;
}

void matrix_init(void) {
    // initialize key pins
    unselect_rows();
    for (uint8_t x = 0; x < MATRIX_COLS; x++) {
        setPinInputHigh_atomic(col_pins[x]);
    }

    debounce_init();
}

uint8_t matrix_update(void) {
    bool changed = false;

    debounce_update();

    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        // set row, read cols
        matrix_row_t row_value = read_cols_on_row(row);

        // scan changed col in row
        for (uint8_t col = 0; col < MATRIX_COLS; col++) {
            if (debounce_is_active(row, col)) continue;

            matrix_row_t mask         = ((matrix_row_t)1) << col;
            matrix_row_t masked_value = (row_value & mask);

            if (masked_value != (matrix[row] & mask)) {
                matrix_button_changed(row, col_order[col], masked_value != 0);
                matrix[row] = (matrix[row] & ~mask) | masked_value;
                debounce_set_active(row, col);
                changed |= true;
            }
        }
    }

    return (uint8_t)changed;
}
