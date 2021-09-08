#include "state_main.h"

#include "midi.h"
#include "leds.h"
#include "bpm.h"
#include "arpeggiator.h"

state_func_t state_func_main = (state_func_t){.init = state_main_init, .enter = state_main_enter, .update = state_main_update, .change_button = state_main_change_button, .exit = state_main_exit};

void state_main_init() { arp_init(); }
void state_main_enter() {}
void state_main_update() { arp_update(); }
void state_main_change_button(uint8_t row, uint8_t col, bool is_pressed) {
    if (row == 0) {
        if (!is_pressed) return;
        switch (col) {
            case 0:
                bpm_set(60);
                break;
            case 1:
                bpm_set(120);
                break;
            case 2:
                bpm_set(200);
                break;
            default:
                break;
        }
    } else {
        row -= 1;
        if (is_pressed)
            arp_start(row, col);
        else
            arp_stop(row, col);
    }
}
void state_main_exit() {}