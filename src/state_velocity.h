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

#include "context.h"

#include <stdint.h>
#include <stdbool.h>

extern state_func_t state_func_velocity;

void state_velocity_init(void);
void state_velocity_enter(void);
void state_velocity_update(void);
void state_velocity_change_button(uint8_t row, uint8_t col, bool is_pressed);
void state_velocity_exit(void);
