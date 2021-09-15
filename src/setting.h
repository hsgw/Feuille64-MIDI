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
#include <stdbool.h>

void setting_enter(void);

void setting_set_scale_row(uint8_t scale);
void setting_set_scale_col(uint8_t scale);
void setting_set_key_note(uint8_t note);
void setting_add_key_oct(int8_t add);
void setting_set_diatonic_mode(uint8_t mode);
void setting_toggle_pitch_mode(void);
void setting_add_bpm(int8_t add);
void setting_toggle_midi_sync();