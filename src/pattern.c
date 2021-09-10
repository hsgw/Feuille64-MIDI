#include "pattern.h"
#include "pattern_default.h"
#include <stdbool.h>

extern pattern_t patterns[PATTERN_COUNT];

static uint8_t current_pattern;

void pattern_init(void) { current_pattern = 0; }

step_t pattern_get_step(uint8_t* step_count) {
    step_t step = patterns[current_pattern].steps[*step_count];
    *step_count += 1;
    if (*step_count >= patterns[current_pattern].length) *step_count = 0;
    return step;
}

void pattern_change(uint8_t pattern) { current_pattern = pattern; }

uint8_t pattern_get_current(void) { return current_pattern; }

void pattern_set_step(uint8_t step, uint8_t row, uint8_t col) {
    patterns[current_pattern].steps[step].row = row;
    patterns[current_pattern].steps[step].col = col;
}