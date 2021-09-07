#include "arpeggiator.h"

#include "DeviceConfig.h"
#include "midi.h"
#include "leds.h"
#include "bpm.h"

#define ARPS_MAX_NUM (8)

typedef enum { ARP_DEAD, ARP_RESERVE, ARP_ALIVE } arp_alive_t;

typedef struct {
    arp_alive_t alive;
    uint8_t     root_row;
    uint8_t     root_col;
    int8_t      step;
    uint8_t     last_note;
    bool        is_playing_note;
} arp_status_t;

arp_status_t arp_status_init(arp_alive_t alive, uint8_t root_row, uint8_t root_col) {
    return (arp_status_t){.alive = alive, .root_row = root_row, .root_col = root_col, .step = 0, .last_note = 0, .is_playing_note = false};
}

static arp_status_t arps[ARPS_MAX_NUM];
static uint8_t      arps_tail;
static uint8_t      current_pattern;

int8_t arp_search_alive(uint8_t row, uint8_t col) {
    for (uint8_t i = 0; i < ARPS_MAX_NUM; i++) {
        if (arps[i].alive != ARP_DEAD && arps[i].root_row == row && arps[i].root_col == col) {
            return i;
        }
    }
    return -1;
}

void arp_init(void) {
    for (int8_t i = 0; i < ARPS_MAX_NUM; i++) {
        arps[i] = arp_status_init(false, 0, 0);
    }
    arps_tail       = 0;
    current_pattern = 0;
}

void arp_update(void) {
    if (!bpm_tick()) return;
    // check global timing
    bool is_global_8_beat_tick = BEAT_CHECK(bpm_get_global_beat_count(), 8, 0);
    for (uint8_t i = 0; i < ARPS_MAX_NUM; i++) {
        if (arps[i].alive == ARP_RESERVE && is_global_8_beat_tick) arps[i].alive = ARP_ALIVE;

        if (arps[i].alive == ARP_ALIVE) {
            arps[i].step++;
            if (arps[i].step == BEAT_COUNT) arps[i].step = 0;

            if (BEAT_CHECK(arps[i].step, 8, 0)) {
                uint8_t note            = 0x30 + arps[i].root_row * 8 + arps[i].root_col;
                arps[i].is_playing_note = true;
                arps[i].last_note       = note;
                midi_send_note(true, note, MIDI_STANDARD_VELOCITY, MIDI_ARP_CHANNEL);
                leds_set(arps[i].root_row, arps[i].root_col, 15);
            } else if (BEAT_CHECK(arps[i].step, 8, BEAT_COUNT - 1)) {
                arps[i].is_playing_note = false;
                midi_send_note(false, arps[i].last_note, MIDI_STANDARD_VELOCITY, MIDI_ARP_CHANNEL);
                leds_set(arps[i].root_row, arps[i].root_col, 0);
            }
        }
    }
}

void arp_start(uint8_t row, uint8_t col) {
    uint8_t index = arp_search_alive(row, col);
    if (index != -1 && arps[index].is_playing_note) {
        arps[index].alive           = ARP_DEAD;
        arps[index].is_playing_note = false;
        midi_send_note(false, arps[index].last_note, MIDI_STANDARD_VELOCITY, MIDI_ARP_CHANNEL);
        leds_set(row, col, 0);
    }
    // stop next if exist and play note
    if (arps[arps_tail].is_playing_note) {
        midi_send_note(false, arps[arps_tail].last_note, MIDI_STANDARD_VELOCITY, MIDI_ARP_CHANNEL);
        leds_set(arps[arps_tail].root_row, arps[arps_tail].root_col, 0);
    }
    // add new one
    arps[arps_tail] = arp_status_init(ARP_RESERVE, row, col);
    arps_tail++;
    if (arps_tail == ARPS_MAX_NUM) arps_tail = 0;
}

void arp_stop(uint8_t row, uint8_t col) {
    uint8_t index = arp_search_alive(row, col);
    if (index != -1) {
        arps[index].alive = ARP_DEAD;
        if (arps[index].is_playing_note) {
            arps[index].is_playing_note = false;
            midi_send_note(false, arps[index].last_note, MIDI_STANDARD_VELOCITY, MIDI_ARP_CHANNEL);
            leds_set(row, col, 0);
        }
    }
}