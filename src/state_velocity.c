#include "state_velocity.h"
#include "pattern.h"
#include "pattern_velocity_edit.h"

state_func_t state_func_velocity =
    (state_func_t){.init = state_velocity_init, .enter = state_velocity_enter, .update = state_velocity_update, .change_button = state_velocity_change_button, .exit = state_velocity_exit};

void state_velocity_init(void) {}

void state_velocity_enter(void) { pattern_velocity_edit_begin_current(); }

void state_velocity_update(void) {}

void state_velocity_change_button(uint8_t row, uint8_t col, bool is_pressed) {
    if (!is_pressed) return;
    if (row == 1) {
        if (col <= PATTERN_COUNT) {
            // change pattern
            pattern_change(col);
            pattern_velocity_edit_begin(col);
        }
    } else {
        // set velocity 2-7
        // set on-off   8
        if (row == 8) {
            pattern_velocity_edit_toggle_enable(col);
        } else {
            pattern_velocity_edit_set_velocity(col, 7 - row);
        }
    }
}

void state_velocity_exit(void) {}