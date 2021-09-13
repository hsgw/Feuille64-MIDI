#pragma once

#include <stdint.h>

void scale_init(void);

void scale_set_scale_row(uint8_t scale);
void scale_set_scale_col(uint8_t col);
void scale_set_pitch_mode(uint8_t mode);
void scale_set_key(uint8_t key);
void scale_set_diatonic_mode(uint8_t mode);

uint8_t scale_get_scale_row(void);
uint8_t scale_get_scale_col(void);
uint8_t scale_get_pitch_mode(void);
uint8_t scale_get_key(void);
uint8_t scale_get_diatonic_mode(void);

uint8_t scale_matrix_to_note_param(uint8_t row, uint8_t col, uint8_t scale_row, uint8_t scale_col, uint8_t pitch_mode, uint8_t key, uint8_t mode);
uint8_t scale_matrix_to_note(uint8_t row, uint8_t col);