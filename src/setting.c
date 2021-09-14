#include "setting.h"
#include "DeviceConfig.h"
#include "scale_defs.h"
#include "scale.h"
#include "bpm.h"
#include "leds.h"

#define SCALE_ROW_LEDS_ROW (0)
#define SCALE_COL_LEDS_ROW (2)

#define SCALE_KEY_LEDS_ROW (4)
#define SCALE_KEY_OCTAVE_COL (4)
#define SCALE_KEY_OCTAVE_NUM (4)

#define SCALE_DIATONIC_MODE_LEDS_ROW (6)

#define SCALE_PITCH_MODE_LEDS_ROW (6)
#define SCALE_PITCH_MODE_LEDS_COL (7)

#define BPM_LEDS_ROW (7)

void set_scale_leds(uint8_t scale, uint8_t start_row, uint8_t r, uint8_t g, uint8_t b) {
    for (uint8_t row = 0; row < 2; row++) {
        for (uint8_t col = 0; col < LED_COL; col++) {
            if (row * 8 + col < SCALE_KIND_NUM)
                leds_set_rgb(row + start_row, col, r, g, b);
            else
                leds_set(row + start_row, col, 0);
        }
    }
    leds_set_rgb(start_row + scale / LED_COL, scale < LED_COL ? scale : scale % LED_COL, 16, 16, 16);
}

void set_key_leds(void) {
    for (uint8_t row = 0; row < 2; row++) {
        for (uint8_t col = 0; col < LED_COL; col++) {
            if (row * 8 + col < SCALE_OCTAVE) {
                leds_set_rgb(row + SCALE_KEY_LEDS_ROW, col, 16, 16, 0);
            } else {
                leds_set_rgb(row + SCALE_KEY_LEDS_ROW, col, 0, 0, 16);
            }
        }
    }

    // set note
    uint8_t key  = scale_get_key();
    uint8_t note = key % SCALE_OCTAVE;
    leds_set_rgb(SCALE_KEY_LEDS_ROW + note / LED_COL, note < LED_COL ? note : note % LED_COL, 16, 16, 16);

    // set octave
    uint8_t oct = key / SCALE_OCTAVE;
    for (uint8_t i = 0; i < SCALE_KEY_OCTAVE_NUM; i++) {
        if (oct & (1 << (SCALE_KEY_OCTAVE_NUM - i - 1))) {
            leds_set_rgb(SCALE_KEY_LEDS_ROW + 1, SCALE_KEY_OCTAVE_COL + i, 16, 16, 16);
        }
    }
}

void set_diatonic_mode_leds(void) {
    for (uint8_t col = 0; col < SCALE_DIATONIC_MODE; col++) {
        leds_set_rgb(SCALE_DIATONIC_MODE_LEDS_ROW, col, 16, 0, 16);
    }
    leds_set_rgb(SCALE_DIATONIC_MODE_LEDS_ROW, scale_get_diatonic_mode(), 16, 16, 16);
}

void set_pitch_mode_leds(void) { leds_set_rgb(SCALE_PITCH_MODE_LEDS_ROW, SCALE_PITCH_MODE_LEDS_COL, scale_get_pitch_mode() ? 16 : 0, 0, 0); }

void set_bpm_leds(void) {
    uint8_t bpm = bpm_get_current_bpm();
    for (uint8_t col = 0; col < LED_COL; col++) {
        leds_set_rgb(BPM_LEDS_ROW, col, 0, 0, bpm & (1 << (LED_COL - col - 1)) ? 16 : 0);
    }
}

void setting_enter(void) {
    leds_set_all(0);
    set_scale_leds(scale_get_scale_row(), SCALE_ROW_LEDS_ROW, 16, 0, 0);
    set_scale_leds(scale_get_scale_col(), SCALE_COL_LEDS_ROW, 0, 16, 0);
    set_key_leds();
    set_diatonic_mode_leds();
    set_pitch_mode_leds();
    set_bpm_leds();
}

void setting_set_scale_row(uint8_t scale) {
    scale_set_scale_row(scale);
    set_scale_leds(scale_get_scale_row(), SCALE_ROW_LEDS_ROW, 16, 0, 0);
}

void setting_set_scale_col(uint8_t scale) {
    scale_set_scale_col(scale);
    set_scale_leds(scale_get_scale_col(), SCALE_COL_LEDS_ROW, 0, 16, 0);
}

void setting_set_key_note(uint8_t note) {
    uint8_t key = scale_get_key();
    uint8_t oct = key / SCALE_OCTAVE;

    scale_set_key(oct * SCALE_OCTAVE + note);
    set_key_leds();
}

void setting_add_key_oct(int8_t add) {
    uint8_t key     = scale_get_key();
    int8_t  new_key = add * SCALE_OCTAVE + key;
    if (new_key < 0 || new_key > 127) new_key = key;

    scale_set_key(new_key);
    set_key_leds();
}

void setting_set_diatonic_mode(uint8_t mode) {
    scale_set_diatonic_mode(mode);
    set_diatonic_mode_leds();
}

void setting_toggle_pitch_mode(void) {
    scale_set_pitch_mode(!scale_get_pitch_mode());
    set_pitch_mode_leds();
}

void setting_add_bpm(int8_t add) {
    bpm_set(bpm_get_current_bpm() + add);
    set_bpm_leds();
}