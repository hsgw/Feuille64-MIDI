#include "state_setting.h"

#include "setting.h"

state_func_t state_func_setting =
    (state_func_t){.init = state_setting_init, .enter = state_setting_enter, .update = state_setting_update, .change_button = state_setting_change_button, .exit = state_setting_exit};

void state_setting_init(void) {}

void state_setting_enter(void) { setting_enter(); }

void state_setting_update(void) {}

void state_setting_change_button(uint8_t row, uint8_t col, bool is_pressed) {
    if (!is_pressed) return;
    switch (row) {
        case 1:
            setting_set_scale_row(col);
            break;
        case 2:
            if (col < 5) setting_set_scale_row(col + 8);
            break;
        case 3:
            setting_set_scale_col(col);
            break;
        case 4:
            if (col < 5) setting_set_scale_col(col + 8);
            break;
        case 5:
            setting_set_key_note(col);
            break;
        case 6:
            if (col < 4) {
                setting_set_key_note(col + 8);
            } else if (col < 6) {
                setting_add_key_oct(1);
            } else {
                setting_add_key_oct(-1);
            }
            break;
        case 7:
            if (col == 7) {
                setting_toggle_pitch_mode();
            } else {
                setting_set_diatonic_mode(col);
            }
            break;
        case 8:
            if (col == 0) {
                setting_add_bpm(10);
            } else if (col == 7) {
                setting_add_bpm(-10);
            } else if (col < 4) {
                setting_add_bpm(1);
            } else {
                setting_add_bpm(-1);
            }
        default:
            break;
    }
}

void state_setting_exit(void) {}