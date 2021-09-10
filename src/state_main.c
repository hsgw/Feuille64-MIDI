#include "state_main.h"

#include "DeviceConfig.h"
#include "midi.h"
#include "leds.h"
#include "bpm.h"
#include "arpeggiator.h"

state_func_t state_func_main = (state_func_t){.init = state_main_init, .enter = state_main_enter, .update = state_main_update, .change_button = state_main_change_button, .exit = state_main_exit};

void state_main_init() { arp_init(); }
void state_main_enter() { arp_restore(); }
void state_main_update() { arp_update(); }
void state_main_change_button(uint8_t row, uint8_t col, bool is_pressed) {
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
void state_main_exit() { arp_clear(); }