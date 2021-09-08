#include "context.h"
#include "state_main.h"

extern state_func_t state_func_main;

state_t current_state;

state_func_t* state_funcs[] = {&state_func_main};

void context_init(void) {
    current_state = STATE_MAIN;
    state_funcs[current_state]->enter();
}
void context_enter(void) { state_funcs[current_state]->enter(); }
void context_update(void) { state_funcs[current_state]->update(); }
void context_change_button(uint8_t row, uint8_t col, bool is_pressed) { state_funcs[current_state]->change_button(row, col, is_pressed); }
void context_change_state(state_t next) {
    state_funcs[current_state]->exit();
    current_state = next;
    state_funcs[current_state]->enter();
}