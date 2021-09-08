/*
 *  Timer for BPM count
 *  use timer1
 */

#pragma once

#include "stdint.h"
#include "stdbool.h"
#include <avr/io.h>

#define BEAT_COUNT (96)
#define BEAT_CHECK(count, beat, offset) (count % (BEAT_COUNT / beat) == offset)

void bpm_init(void);

// 60-200 bpm
void bpm_set(uint8_t bpm);

// check tick(1/96 beat) and update global beat count
bool bpm_tick(void);

uint8_t bpm_get_current_bpm(void);
uint8_t bpm_get_global_beat_count(void);
uint8_t bpm_reset_beat(void);