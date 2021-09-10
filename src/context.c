#include "context.h"
#include "state_main.h"
#include "state_pattern.h"

extern state_func_t state_func_main;
extern state_func_t state_func_pattern;

state_t current_state;

state_func_t* state_funcs[] = {&state_func_main, &state_func_pattern};

void context_init(void) {
    current_state = STATE_MAIN;
    state_funcs[current_state]->enter();
}
void context_enter(void) { state_funcs[current_state]->enter(); }
void context_update(void) { state_funcs[current_state]->update(); }
void context_change_button(uint8_t row, uint8_t col, bool is_pressed) {
    if (row == 0) {
        switch (col) {
            case 0:
                context_change_state(STATE_MAIN);
                break;
            case 1:
                context_change_state(STATE_PATTERN);
            default:
                break;
        }
    } else {
        state_funcs[current_state]->change_button(row, col, is_pressed);
    }
}
void context_change_state(state_t next) {
    state_funcs[current_state]->exit();
    current_state = next;
    state_funcs[current_state]->enter();
}