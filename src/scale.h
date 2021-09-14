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

void scale_init(void);

void scale_set_scale_row(uint8_t scale);
void scale_set_scale_col(uint8_t col);
void scale_set_pitch_mode(bool mode);
void scale_set_key(uint8_t k);
void scale_set_diatonic_mode(uint8_t mode);

uint8_t scale_get_scale_row(void);
uint8_t scale_get_scale_col(void);
bool    scale_get_pitch_mode(void);
uint8_t scale_get_key(void);
uint8_t scale_get_diatonic_mode(void);

uint8_t scale_matrix_to_note_param(uint8_t row, uint8_t col, uint8_t scale_row, uint8_t scale_col, uint8_t pitch_mode, uint8_t key, uint8_t mode);
uint8_t scale_matrix_to_note(uint8_t row, uint8_t col);