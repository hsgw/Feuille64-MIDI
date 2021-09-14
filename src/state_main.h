#pragma once
#include "context.h"

#include "stdint.h"
#include "stdbool.h"

extern state_func_t state_func_main;

void state_main_init(void);
void state_main_enter(void);
void state_main_update(void);
void state_main_change_button(uint8_t row, uint8_t col, bool is_pressed);
void state_main_exit(void);
