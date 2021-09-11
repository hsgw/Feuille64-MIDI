#include "arpeggiator.h"

#include "DeviceConfig.h"
#include "midi.h"
#include "leds.h"
#include "bpm.h"
#include "pattern.h"

// polyphony
#define ARPS_MAX_NUM (8)
// 1/n beat
#define ARPS_BEAT_GRID (16)
// #define ARPS_ALLOW_BEAT_OFFSET (2)

typedef enum { ARP_DEAD, ARP_RESERVE, ARP_ALIVE } arp_alive_t;

typedef struct {
    arp_alive_t alive;
    uint8_t     root_row;
    uint8_t     root_col;
    int8_t      count;
    uint8_t     last_note;
    bool        is_playing_note;
    uint8_t     last_calc_row;
    uint8_t     last_calc_col;
    uint8_t     step;
} arp_status_t;

arp_status_t arp_status_create(arp_alive_t alive, uint8_t root_row, uint8_t root_col) {
    return (arp_status_t){.alive = alive, .root_row = root_row, .root_col = root_col, .count = 0, .last_note = 0, .is_playing_note = false, .last_calc_row = 0, .last_calc_col = 0, .step = 0};
}

static arp_status_t arps[ARPS_MAX_NUM];
static uint8_t      arps_tail;
static bool         hold;

inline uint8_t calc_position(int8_t root, int8_t add, uint8_t max) {
    int8_t calc = root + add;
    if (calc < 0)
        calc = calc + max;
    else if (calc >= max)
        calc = calc - max;
    return (uint8_t)calc;
}

inline void apply_status(bool on, arp_status_t* status, uint8_t vel) {
    midi_send_note(on, status->last_note, vel, MIDI_ARP_CHANNEL);
    leds_set(status->last_calc_row + 1, status->last_calc_col, on ? 15 : 0);
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
    if (!bpm_tick()) return;
    // check global timing
    bool is_global_beat_tick = BEAT_CHECK_ON(bpm_get_global_beat_count(), ARPS_BEAT_GRID);

    for (uint8_t i = 0; i < ARPS_MAX_NUM; i++) {
        if (arps[i].alive == ARP_RESERVE) {
            if (is_global_beat_tick) arps[i].alive = ARP_ALIVE;
            // else if (global_beat_offset <= ARPS_ALLOW_BEAT_OFFSET) {
            //     arps[i].alive           = ARP_ALIVE;
            //     uint8_t note            = 0x30 + arps[i].root_row * 8 + arps[i].root_col;
            //     arps[i].is_playing_note = true;
            //     arps[i].last_note       = note;
            //     arps[i].count           = global_beat_offset;
            //     midi_send_note(true, note, MIDI_STANDARD_VELOCITY, MIDI_ARP_CHANNEL);
            //     leds_set(arps[i].root_row, arps[i].root_col, 15);
            //     return;
            // }
        }

        if (arps[i].alive == ARP_ALIVE) {
            // get step and play note
            if (BEAT_CHECK_ON(arps[i].count, ARPS_BEAT_GRID)) {
                if (arps[i].is_playing_note) {
                    // note off
                    apply_status(false, &arps[i], MIDI_STANDARD_VELOCITY);
                    arps[i].is_playing_note = false;
                }
                // note on
                step_t step = pattern_next_step(&(arps[i].step));
                if (step.enable) {
                    arps[i].is_playing_note = true;
                    arps[i].last_calc_row   = calc_position(arps[i].root_row, step.row, MATRIX_ROWS - 2);
                    arps[i].last_calc_col   = calc_position(arps[i].root_col, step.col, MATRIX_COLS);
                    arps[i].last_note       = 0x20 + arps[i].last_calc_row * 8 + arps[i].last_calc_col;

                    apply_status(true, &arps[i], VELOCITY_TABLE[step.vel]);
                }
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
            leds_set(arps[i].last_calc_row, arps[i].last_calc_col, 15);
        }
    }
}