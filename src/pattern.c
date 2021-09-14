/*   Copyright 2021 Takuya Urakawa (hsgw)
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

#include "pattern.h"

#include "pattern_default.h"
#include <stdbool.h>

extern pattern_t patterns[PATTERN_COUNT];

static uint8_t current_pattern;

void pattern_init(void) { current_pattern = 0; }

next_step_t pattern_step(uint8_t step_count) {
    step_t step = patterns[current_pattern].steps[step_count];
    step_count += 1;
    if (step_count >= patterns[current_pattern].length) step_count = 0;
    return (next_step_t){.step = step, .next_step_count = step_count};
}

void pattern_change(uint8_t pattern) { current_pattern = pattern; }

uint8_t pattern_get_current(void) { return current_pattern; }
step_t  pattern_get_step(uint8_t step_count) { return patterns[current_pattern].steps[step_count]; }
uint8_t pattern_get_length(void) { return patterns[current_pattern].length; }

void pattern_set_step(uint8_t step, uint8_t row, uint8_t col) {
    patterns[current_pattern].steps[step].row = row;
    patterns[current_pattern].steps[step].col = col;
}
void pattern_set_velocity(uint8_t step, uint8_t velocity) { patterns[current_pattern].steps[step].vel = velocity; }
void pattern_set_length(uint8_t length) { patterns[current_pattern].length = length; }
void pattern_toggle_enable(uint8_t step) { patterns[current_pattern].steps[step].enable = !patterns[current_pattern].steps[step].enable; }
