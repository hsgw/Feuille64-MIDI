#include "pattern_velocity_edit.h"
#include "leds.h"
#include "pattern.h"

void set_step_leds(uint8_t count) {
    step_t step = pattern_get_step(count);
    leds_set(7, count, step.enable ? 15 : 0);
    uint8_t top_row = 6 - step.vel;
    for (uint8_t i = 1; i < 7; i++) {
        leds_set(i, count, i >= top_row ? 15 : 0);
    }
}

void pattern_velocity_edit_begin(uint8_t pattern) {
    leds_set_all(0);
    leds_set_rgb(0, pattern_get_current(), 0, 32, 0);
    for (uint8_t i = 0; i < PATTERN_STEP_MAX; i++) {
        set_step_leds(i);
    }
}

void pattern_velocity_edit_begin_current(void) { pattern_velocity_edit_begin(pattern_get_current()); }

void pattern_velocity_edit_set_velocity(uint8_t step, uint8_t velocity) {
    pattern_set_velocity(step, velocity);
    set_step_leds(step);
}

void pattern_velocity_edit_toggle_enable(uint8_t step) {
    pattern_toggle_enable(step);
    set_step_leds(step);
}
