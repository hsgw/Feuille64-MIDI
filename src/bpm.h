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

/*
 *  Timer for BPM count
 *  use timer1
 */

#pragma once

#include "stdint.h"
#include "stdbool.h"

#define BEAT_COUNT (96)
#define BEAT_CHECK_ON(count, beat) (count % (BEAT_COUNT / beat) == 0)

void bpm_init(void);

// 60-200 bpm
void bpm_set(uint8_t bpm);

// check tick(1/96 beat) and update global beat count
bool bpm_update(void);

uint8_t bpm_get_current_bpm(void);
uint8_t bpm_get_global_beat_count(void);
void    bpm_reset(void);

void bpm_set_midi_sync(bool flag);
bool bpm_get_midi_sync(void);

void bpm_set_midi_started(void);
void bpm_set_midi_stopped(void);
void bpm_tick(void);