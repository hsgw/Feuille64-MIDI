#include "pattern_edit.h"
#include "pattern.h"
#include "leds.h"

#include <stdbool.h>

static uint8_t current_edit_root_row;
static uint8_t current_edit_root_col;
static uint8_t current_edit_step;
static uint8_t prev_edit_row;
static uint8_t prev_edit_col;

void pattern_edit_step_begin(uint8_t pattern) {
    leds_set_all(0);
    leds_set_rgb(0, pattern, 32, 0, 0);
    prev_edit_row = 0;
    prev_edit_col = 0;
    pattern_change(pattern);
}

void pattern_edit_step_begin_current(void) { pattern_edit_step_begin(pattern_get_current()); }

void pattern_edit_step_step(uint8_t row, uint8_t col) {
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

void set_step_velocity_leds(uint8_t count) {
    step_t  step  = pattern_get_step(count);
    uint8_t color = step.enable ? 16 : 0;
    leds_set_rgb(6, count, color, 0, 0);
    uint8_t top_row = 5 - step.vel;
    for (uint8_t i = 1; i < 6; i++) {
        leds_set(i, count, i >= top_row ? 15 : 0);
    }
}

void set_length_leds(void) {
    uint8_t length = pattern_get_length() - 1;
    for (uint8_t i = 0; i < 8; i++) {
        uint8_t color = i <= length ? 16 : 0;
        leds_set_rgb(7, i, 0, 0, color);
    }
}

void pattern_edit_velocity_begin(uint8_t pattern) {
    leds_set_all(0);
    leds_set_rgb(0, pattern_get_current(), 0, 32, 0);
    for (uint8_t i = 0; i < PATTERN_STEP_MAX; i++) {
        set_step_velocity_leds(i);
    }
    set_length_leds();
}

void pattern_edit_velocity_begin_current(void) { pattern_edit_velocity_begin(pattern_get_current()); }

void pattern_edit_velocity_set_velocity(uint8_t step, uint8_t velocity) {
    pattern_set_velocity(step, velocity);
    set_step_velocity_leds(step);
}

void pattern_edit_velocity_toggle_enable(uint8_t step) {
    pattern_toggle_enable(step);
    set_step_velocity_leds(step);
}

void pattern_edit_velocity_set_length(uint8_t length) {
    pattern_set_length(length);
    set_length_leds();
}
