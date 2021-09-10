#include "pattern_step_edit.h"
#include "pattern.h"
#include "leds.h"

#include <stdbool.h>

static uint8_t current_edit_root_row;
static uint8_t current_edit_root_col;
static uint8_t current_edit_step;
static uint8_t prev_edit_row;
static uint8_t prev_edit_col;

void pattern_step_edit_begin(uint8_t pattern) {
    leds_set_all(0);
    leds_set_rgb(0, pattern, 32, 0, 0);
    prev_edit_row = 0;
    prev_edit_col = 0;
    pattern_change(pattern);
}

void pattern_step_edit_begin_current(void) { pattern_step_edit_begin(pattern_get_current()); }

void pattern_step_edit_step(uint8_t row, uint8_t col) {
    if (current_edit_step == 0) {
        current_edit_root_row = row;
        current_edit_root_col = col;
    } else {
        pattern_set_step(current_edit_step, row - current_edit_root_row, col - current_edit_root_col);
    }

    current_edit_step++;
    if (current_edit_step == PATTERN_STEP_MAX) current_edit_step = 0;

    leds_set(prev_edit_row + 1, prev_edit_col, 0);
    leds_set(row + 1, col, 15);
    prev_edit_row = row;
    prev_edit_col = col;
}

void pattern_step_edit_end(void) {}