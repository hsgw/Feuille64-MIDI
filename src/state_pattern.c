#include "state_pattern.h"
#include "pattern.h"
#include "pattern_edit.h"

state_func_t state_func_pattern =
    (state_func_t){.init = state_pattern_init, .enter = state_pattern_enter, .update = state_pattern_update, .change_button = state_pattern_change_button, .exit = state_pattern_exit};

void state_pattern_init(void) { pattern_init(); }

void state_pattern_enter(void) { pattern_edit_step_begin_current(); }

void state_pattern_update(void) {}

void state_pattern_change_button(uint8_t row, uint8_t col, bool is_pressed) {
    if (!is_pressed) return;
    if (row == 1) {
        if (col <= PATTERN_COUNT) {
            pattern_edit_step_begin(col);
        }
    } else {
        pattern_edit_step_step(row - 2, col);
    }
}

void state_pattern_exit(void) {}