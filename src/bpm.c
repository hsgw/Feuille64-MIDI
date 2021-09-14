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

#include "bpm.h"

#include <avr/io.h>

#define BPM_DEFAULT (100)

// F_CPU / prescaler * 60 / beat(4*n = 96) / bpm
#define BPM_TO_CNT_96(bpm) (uint16_t)(F_CPU / 64 * 60 / 24 / bpm - 1)

#define BPM_GET_FLAG() (TIFR1 & _BV(OCF1A))
#define BPM_CLEAR_FLAG() (TIFR1 |= _BV(OCF1A))

static uint8_t current_bpm       = BPM_DEFAULT;
static uint8_t global_beat_count = 0;

static bool    sync_midi        = false;
static bool    has_started_midi = false;
static uint8_t midi_tick_count  = 0;

void bpm_init(void) {
    // init timer1
    TCCR1A = 0;
    TCCR1B = _BV(WGM12) | _BV(CS11) | _BV(CS10);  // CTC, 1/64 pre scaler

    bpm_set(current_bpm);
}

void bpm_set(uint8_t bpm) {
    if (bpm < 60)
        current_bpm = 60;
    else if (bpm > 200)
        current_bpm = 200;
    else
        current_bpm = bpm;

    global_beat_count = 0;

    OCR1A = BPM_TO_CNT_96(bpm);
    TCNT1 = 0;

    BPM_CLEAR_FLAG();
}

// 1/96 beat
bool bpm_update(void) {
    bool flag = false;

    if (sync_midi) {
        if (midi_tick_count > 0) {
            global_beat_count += midi_tick_count;
            midi_tick_count = 0;
            flag            = true;
        }
    } else {
        flag = BPM_GET_FLAG();
        if (flag) {
            BPM_CLEAR_FLAG();
            global_beat_count++;
            if (global_beat_count == BEAT_COUNT) global_beat_count = 0;
        }
    }
    return flag;
}

uint8_t bpm_get_current_bpm(void) { return current_bpm; }

uint8_t bpm_get_global_beat_count(void) { return global_beat_count; }

void bpm_reset(void) { bpm_set(current_bpm); }

// midi sync
void bpm_set_midi_sync(bool flag) {
    sync_midi = flag;
    if (!sync_midi) {
        bpm_reset();
    }
};

bool bpm_get_midi_sync(void) { return sync_midi; };

void bpm_set_midi_started(void) {
    if (!sync_midi) return;
    midi_tick_count  = 0;
    has_started_midi = true;
}

void bpm_set_midi_stopped(void) {
    if (!sync_midi) return;
    has_started_midi = false;
}

void bpm_tick(void) {
    if (sync_midi && has_started_midi) midi_tick_count++;
}