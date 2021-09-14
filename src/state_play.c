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

#include "state_play.h"

#include "DeviceConfig.h"
#include "midi.h"
#include "leds.h"
#include "bpm.h"
#include "arpeggiator.h"

state_func_t state_func_play = (state_func_t){.init = state_play_init, .enter = state_play_enter, .update = state_play_update, .change_button = state_play_change_button, .exit = state_play_exit};

void state_play_init(void) { arp_init(); }
void state_play_enter(void) { arp_restore(); }
void state_play_update(void) { arp_update(); }
void state_play_change_button(uint8_t row, uint8_t col, bool is_pressed) {
    if (row == 1) {
        // 1st row is setting
        if (col < PATTERN_COUNT) {
            if (is_pressed) arp_change_pattern(col);
        } else if (col == 7) {
            if (is_pressed) arp_toggle_hold();
        }
    } else {
        // key matrix is 7x8
        if (is_pressed)
            arp_start(row - 2, col);
        else
            arp_stop(row - 2, col);
    }
}
void state_play_exit(void) { arp_clear(); }