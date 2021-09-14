/*
 *  Timer for BPM count
 *  use timer1
 */

#pragma once

#include "stdint.h"
#include "stdbool.h"
#include <avr/io.h>

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