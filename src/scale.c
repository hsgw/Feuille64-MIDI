#include "scale.h"
#include "scale_defs.h"

#define SCALE_DEFALUT_ROW_SCALE (2)
#define SCALE_DEFAULT_COL_SCALE (3)
#define SCALE_DEFAULT_PITCH_MODE (2)
#define SCALE_DEFAULT_KEY (36)
#define SCALE_DEFAULT_DIATONIC_MODE (5)

static uint8_t scale_row     = SCALE_DEFALUT_ROW_SCALE;
static uint8_t scale_col     = SCALE_DEFAULT_COL_SCALE;
static uint8_t pitch_mode    = SCALE_DEFAULT_PITCH_MODE;
static uint8_t key           = SCALE_DEFAULT_KEY;
static uint8_t diatonic_mode = SCALE_DEFAULT_DIATONIC_MODE;

void scale_init(void) {}

void scale_set_scale_row(uint8_t scale) { scale_row = scale; }
void scale_set_scale_col(uint8_t scale) { scale_col = scale; }
void scale_set_pitch_mode(uint8_t mode) { pitch_mode = mode; }
void scale_set_key(uint8_t key) { key = key; }
void scale_set_diatonic_mode(uint8_t mode) { diatonic_mode = mode; }

uint8_t scale_get_scale_row(void) { return scale_row; }
uint8_t scale_get_scale_col(void) { return scale_col; }
uint8_t scale_get_pitch_mode(void) { return pitch_mode; }
uint8_t scale_get_key(void) { return key; }
uint8_t scale_get_diatonic_mode(void) { return diatonic_mode; }

uint8_t scale_matrix_to_note_param(uint8_t row, uint8_t col, uint8_t scale_row, uint8_t scale_col, uint8_t pitch_mode, uint8_t key, uint8_t diatonic_mode) {
    uint8_t base = SCALE_SEED_TABLE[scale_row][row] + SCALE_SEED_TABLE[scale_col][col];
    switch (pitch_mode) {
        case 0:
            return 0;
        case 1:
            // chromatic
            return base + key;
        case 2:
            // diatonic
            // chrmod
            base += SCALE_CHRMOD_TABLE[base % 12];
            // satori
            return base + SCALE_DIATONIC_TABLE[diatonic_mode][base % 12] + key;
        default:
            return 0;
    }
}

uint8_t scale_matrix_to_note(uint8_t row, uint8_t col) { return scale_matrix_to_note_param(row, col, scale_row, scale_col, pitch_mode, key, diatonic_mode); }