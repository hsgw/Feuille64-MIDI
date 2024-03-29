/*   Copyright 2021 Takuya Urakawa (hsgw)
 *
 *   This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 2 of the License, or
 *   (at your option) any later version.

 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include "context.h"

#include "state_play.h"
#include "state_pattern.h"
#include "state_velocity.h"
#include "state_setting.h"
#include "midi.h"
#include "bpm.h"

#include "DeviceConfig.h"

static state_t current_state;

static state_func_t* state_funcs[] = {&state_func_play, &state_func_pattern, &state_func_velocity, &state_func_setting};

void context_init(void) {
    current_state = STATE_MAIN;
    for (uint8_t i = 0; i < STATE_NUM; i++) {
        state_funcs[i]->init();
    }
    state_funcs[current_state]->enter();
}

void context_enter(void) { state_funcs[current_state]->enter(); }

void context_update(void) { state_funcs[current_state]->update(); }

void context_change_button(uint8_t row, uint8_t col, bool is_pressed) {
    if (row == 0) {
        if (!is_pressed) return;
        switch (col) {
            case 0:
                context_change_state(STATE_MAIN);
                break;
            case 1:
                context_change_state(STATE_PATTERN);
                break;
            case 2:
                context_change_state(STATE_VELOCITY);
                break;
            case 3:
                context_change_state(STATE_SETTING);
                break;
            case 5:
                midi_all_note_off(MIDI_ARP_CHANNEL);
                break;
            case 7:
                midi_all_note_off(MIDI_ARP_CHANNEL);
                break;
            default:
                break;
        }
    } else {
        state_funcs[current_state]->change_button(row, col, is_pressed);
    }
}

void context_change_state(state_t next) {
    if (current_state != next) {
        state_funcs[current_state]->exit();
        current_state = next;
        state_funcs[current_state]->enter();
    }
}