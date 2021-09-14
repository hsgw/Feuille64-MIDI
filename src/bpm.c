#include "bpm.h"

#define BPM_DEFAULT (100)

// F_CPU / prescaler * 60 / beat(4*n = 96) / bpm
#define BPM_TO_CNT_96(bpm) (uint16_t)(F_CPU / 64 * 60 / 24 / bpm - 1)

#define BPM_GET_FLAG() (TIFR1 & _BV(OCF1A))
#define BPM_CLEAR_FLAG() (TIFR1 |= _BV(OCF1A))

uint8_t current_bpm       = BPM_DEFAULT;
uint8_t global_beat_count = 0;

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
bool bpm_tick(void) {
    bool flag = BPM_GET_FLAG();
    if (flag) {
        BPM_CLEAR_FLAG();
        global_beat_count++;
        if (global_beat_count == BEAT_COUNT) global_beat_count = 0;
    }
    return flag;
}

uint8_t bpm_get_current_bpm(void) { return current_bpm; }

uint8_t bpm_get_global_beat_count(void) { return global_beat_count; }

void bpm_reset(void) { bpm_set(current_bpm); }