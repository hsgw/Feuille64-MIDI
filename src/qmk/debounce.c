#include "debounce.h"
#include "matrix.h"
#include "timer.h"
#include <stdlib.h>

#ifndef DEBOUNCE
#    define DEBOUNCE 5
#endif

#define ROW_SHIFTER ((matrix_row_t)1)

#define DEBOUNCE_ELAPSED 251
#define MAX_DEBOUNCE (DEBOUNCE_ELAPSED - 1)

#define debounce_counter_t uint8_t

static debounce_counter_t debounce_counters[MATRIX_ROWS][MATRIX_COLS];
static debounce_counter_t current_time;
static bool               counters_update_need;

static uint8_t wrapping_timer_read(void) {
    static uint16_t time        = 0;
    static uint8_t  last_result = 0;
    uint16_t        new_time    = timer_read();
    uint16_t        diff        = new_time - time;
    time                        = new_time;
    last_result                 = (last_result + diff) % (MAX_DEBOUNCE + 1);
    return last_result;
}

void debounce_init() {
    for (uint8_t r = 0; r < MATRIX_ROWS; r++) {
        for (uint8_t c = 0; c < MATRIX_COLS; c++) {
            debounce_counters[r][c] = DEBOUNCE_ELAPSED;
        }
    }
    counters_update_need = false;
}

void debounce_update() {
    debounce_counter_t *counter      = debounce_counters;
    uint8_t             current_time = wrapping_timer_read();

    counters_update_need = false;
    for (uint8_t i = 0; i < MATRIX_ROWS * MATRIX_COLS; i++) {
        if (*counter != DEBOUNCE_ELAPSED) {
            if (TIMER_DIFF(current_time, *counter, MAX_DEBOUNCE) >= DEBOUNCE) {
                *counter = DEBOUNCE_ELAPSED;
            } else {
                counters_update_need = true;
            }
        }
        counter++;
    }
}

bool debounce_is_active(uint8_t row, uint8_t col) { return debounce_counters[row][col] != DEBOUNCE_ELAPSED; }

void debounce_set_active(uint8_t row, uint8_t col) { debounce_counters[row][col] = current_time; }