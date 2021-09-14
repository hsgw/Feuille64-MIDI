#pragma once

#include <stdint.h>
#include <stdbool.h>

void setting_enter(void);

void setting_set_scale_row(uint8_t scale);
void setting_set_scale_col(uint8_t scale);
void setting_set_key_note(uint8_t note);
void setting_add_key_oct(int8_t add);
void setting_set_diatonic_mode(uint8_t mode);
void setting_toggle_pitch_mode(void);