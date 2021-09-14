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

#include "arpeggiator.h"

#include "DeviceConfig.h"
#include "midi.h"
#include "leds.h"
#include "bpm.h"
#include "pattern.h"
#include "scale.h"

// polyphony
#define ARPS_MAX_NUM (8)
// 1/n beat
#define ARPS_BEAT_GRID (16)
// #define ARPS_ALLOW_BEAT_OFFSET (2)

typedef enum { ARP_DEAD, ARP_RESERVE, ARP_ALIVE } arp_alive_t;

typedef struct {
    uint8_t pos;
    bool    reversed;
} arp_pos_t;
typedef struct {
    arp_alive_t alive;
    uint8_t     root_row;
    uint8_t     root_col;
    int8_t      count;
    uint8_t     last_note;
    bool        is_playing_note;
    arp_pos_t   last_row;
    arp_pos_t   last_col;
    uint8_t     step_count;
} arp_status_t;

arp_status_t arp_status_create(arp_alive_t alive, uint8_t root_row, uint8_t root_col) {
    return (arp_status_t){
        .alive           = alive,
        .root_row        = root_row,
        .root_col        = root_col,
        .count           = 0,
        .last_note       = 0,
        .is_playing_note = false,
        .last_row        = (arp_pos_t){.pos = 0, .reversed = false},
        .last_col        = (arp_pos_t){.pos = 0, .reversed = false},
        .step_count      = 0,
    };
}

static arp_status_t arps[ARPS_MAX_NUM];
static uint8_t      arps_tail;
static bool         hold;

inline arp_pos_t calc_position(arp_pos_t prev, int8_t add, uint8_t max) {
    bool   reversed = prev.reversed;
    int8_t pos      = prev.pos + (reversed ? add * -1 : add);

    if (pos < 0) {
        pos      = 0 - pos;
        reversed = !reversed;
    } else if (pos >= max) {
        pos      = max - (pos - max) - 2;
        reversed = !reversed;
    }

    return (arp_pos_t){.pos = pos, .reversed = reversed};
}

inline void apply_status(bool on, arp_status_t* status, uint8_t vel) {
    midi_send_note(on, status->last_note, vel, MIDI_ARP_CHANNEL);
    leds_set(status->last_row.pos + 1, status->last_col.pos, on ? 15 : 0);
}

// void debug_count(uint8_t num) {
//     for (uint8_t i = 0; i < 8; i++) {
//         leds_set(7, i, (num & _BV(i)) ? 15 : 0);
//     }
// }

arp_status_t arp_status_remove(uint8_t row, uint8_t col) {
    arp_status_t removed = arp_status_create(ARP_DEAD, 0, 0);
    bool         found   = false;
    for (int8_t i = 0; i < ARPS_MAX_NUM; i++) {
        if (!found && arps[i].root_row == row && arps[i].root_col == col) {
            found   = true;
            removed = arps[i];
        }
        if (found) {
            if (i == ARPS_MAX_NUM - 1)
                arps[i] = arp_status_create(ARP_DEAD, 0, 0);
            else
                arps[i] = arps[i + 1];
        }
        if (arps[i].alive == ARP_DEAD) {
            arps_tail = i;
            return removed;
        }
    }
    return removed;
}

arp_status_t arp_status_push(uint8_t row, uint8_t col) {
    arp_status_t removed = arp_status_create(ARP_DEAD, 0, 0);

    if (arps_tail < ARPS_MAX_NUM) {
        arps[arps_tail] = arp_status_create(ARP_RESERVE, row, col);
        arps_tail++;
        return removed;
    }

    // arps is full. remove top
    removed         = arp_status_remove(arps[0].root_row, arps[0].root_col);
    arps[arps_tail] = arp_status_create(ARP_RESERVE, row, col);
    arps_tail++;
    return removed;
}

void arp_init(void) {
    for (int8_t i = 0; i < ARPS_MAX_NUM; i++) {
        arps[i] = arp_status_create(ARP_DEAD, 0, 0);
    }
    arps_tail = 0;
}

void arp_update(void) {
    if (!bpm_update()) return;
    // check global timing
    bool is_global_beat_tick = BEAT_CHECK_ON(bpm_get_global_beat_count(), ARPS_BEAT_GRID);

    for (uint8_t i = 0; i < ARPS_MAX_NUM; i++) {
        if (arps[i].alive == ARP_RESERVE) {
            if (is_global_beat_tick) arps[i].alive = ARP_ALIVE;
        }

        if (arps[i].alive == ARP_ALIVE) {
            // get step and play note
            if (BEAT_CHECK_ON(arps[i].count, ARPS_BEAT_GRID)) {
                if (arps[i].is_playing_note) {
                    // note off
                    apply_status(false, &arps[i], MIDI_STANDARD_VELOCITY);
                    arps[i].is_playing_note = false;
                }

                if (arps[i].step_count == 0) {
                    arps[i].last_row.pos      = arps[i].root_row;
                    arps[i].last_row.reversed = false;
                    arps[i].last_col.pos      = arps[i].root_col;
                    arps[i].last_col.reversed = false;
                }

                // note on
                next_step_t next = pattern_step(arps[i].step_count);
                if (next.step.enable) {
                    arps[i].is_playing_note = true;

                    arps[i].last_row = calc_position(arps[i].last_row, next.step.row, MATRIX_ROWS - 2);

                    arps[i].last_col = calc_position(arps[i].last_col, next.step.col, MATRIX_COLS);

                    arps[i].last_note = scale_matrix_to_note(arps[i].last_row.pos, arps[i].last_col.pos);

                    apply_status(true, &arps[i], VELOCITY_TABLE[next.step.vel]);
                }
                arps[i].step_count = next.next_step_count;
            }

            arps[i].count++;
            if (arps[i].count == BEAT_COUNT) arps[i].count = 0;
        }
    }
}

void arp_start(uint8_t row, uint8_t col) {
    if (hold) {
        // try to remove same root
        arp_status_t removed = arp_status_remove(row, col);
        if (removed.is_playing_note) {
            apply_status(false, &removed, MIDI_STANDARD_VELOCITY);
        }
        // if not found, add new one
        if (removed.alive == ARP_DEAD) {
            removed = arp_status_push(row, col);
            if (removed.is_playing_note) {
                apply_status(false, &removed, MIDI_STANDARD_VELOCITY);
            }
        }
    } else {
        // remove same root
        arp_status_t removed = arp_status_remove(row, col);
        if (removed.is_playing_note) {
            apply_status(false, &removed, MIDI_STANDARD_VELOCITY);
        }
        // add new one
        removed = arp_status_push(row, col);
        if (removed.is_playing_note) {
            apply_status(false, &removed, MIDI_STANDARD_VELOCITY);
        }
    }
}

void arp_stop(uint8_t row, uint8_t col) {
    if (hold) return;
    arp_status_t removed = arp_status_remove(row, col);
    if (removed.is_playing_note) {
        apply_status(false, &removed, MIDI_STANDARD_VELOCITY);
    }
}

void arp_clear(void) {
    for (uint8_t i = 0; i < ARPS_MAX_NUM; i++) {
        arps[i].alive = ARP_DEAD;
        if (arps[i].is_playing_note) {
            apply_status(false, &arps[i], MIDI_STANDARD_VELOCITY);
        }
        arps[i].is_playing_note = false;
    }
    hold = false;
}

void arp_change_pattern(uint8_t no) {
    leds_set(0, pattern_get_current(), 0);
    pattern_change(no);
    leds_set(0, no, 15);
}

void arp_toggle_hold(void) {
    hold = !hold;
    if (!hold) arp_clear();
    leds_set(0, 7, hold ? 15 : 0);
}

bool arp_is_in_hold(void) { return hold; }

void arp_restore(void) {
    // restore leds
    leds_set_all(0);
    leds_set(0, pattern_get_current(), 15);
    leds_set(0, 7, hold ? 15 : 0);
    for (uint8_t i = 0; i < ARPS_MAX_NUM; i++) {
        if (arps[i].is_playing_note) {
            leds_set(arps[i].last_row.pos, arps[i].last_col.pos, 15);
        }
    }
}