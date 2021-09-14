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

#pragma once

#include <stdint.h>

void pattern_edit_step_begin(uint8_t no);
void pattern_edit_step_begin_current(void);
void pattern_edit_step_step(uint8_t row, uint8_t col);

void pattern_edit_velocity_begin(uint8_t pattern);
void pattern_edit_velocity_begin_current(void);
void pattern_edit_velocity_set_velocity(uint8_t step, uint8_t velocity);
void pattern_edit_velocity_set_length(uint8_t length);
void pattern_edit_velocity_toggle_enable(uint8_t step);
void pattern_edit_velocity_toggle_enable(uint8_t length);