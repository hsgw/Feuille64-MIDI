#pragma once
#include "context.h"

#include "stdint.h"
#include "stdbool.h"

extern state_func_t state_func_pattern;

void state_pattern_init(void);
void state_pattern_enter(void);
void state_pattern_update(void);
void state_pattern_change_button(uint8_t row, uint8_t col, bool is_pressed);
void state_pattern_exit(void);
