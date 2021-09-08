#include "pattern.h"
#include "pattern_default.h"

extern pattern_t patterns[PATTERN_COUNT];

static uint8_t current_pattern;

void pattern_init() { current_pattern = 0; }

step_t pattern_get_step(uint8_t* step_count) {
    step_t step = patterns[current_pattern].steps[*step_count];
    *step_count += 1;
    if (*step_count >= patterns[current_pattern].length) *step_count = 0;
    return step;
}

void    pattern_change(uint8_t no) { current_pattern = no; }
uint8_t pattern_get_current() { return current_pattern; }
void    pattern_edit_begin(uint8_t pattern) {}
void    pattern_edit_begin_current(void) { pattern_edit_begin(current_pattern); }
void    pattern_edit_step(uint8_t row, uint8_t col) {}
void    pattern_edit_end() {}