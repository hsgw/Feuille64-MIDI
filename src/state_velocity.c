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

#include "state_velocity.h"

#include "pattern.h"
#include "pattern_edit.h"

state_func_t state_func_velocity =
    (state_func_t){.init = state_velocity_init, .enter = state_velocity_enter, .update = state_velocity_update, .change_button = state_velocity_change_button, .exit = state_velocity_exit};

void state_velocity_init(void) {}

void state_velocity_enter(void) { pattern_edit_velocity_begin_current(); }

void state_velocity_update(void) {}

void state_velocity_change_button(uint8_t row, uint8_t col, bool is_pressed) {
    if (!is_pressed) return;
    if (row == 1) {
        if (col <= PATTERN_COUNT) {
            // change pattern
            pattern_change(col);
            pattern_edit_velocity_begin(col);
        }
    } else {
        // set velocity 2-6
        // set on-off   7
        // set length 8
        if (row == 8) {
            pattern_edit_velocity_set_length(col + 1);
        } else if (row == 7) {
            pattern_edit_velocity_toggle_enable(col);
        } else {
            pattern_edit_velocity_set_velocity(col, 6 - row);
        }
    }
}

void state_velocity_exit(void) {}