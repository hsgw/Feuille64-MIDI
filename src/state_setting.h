#pragma once

#include "context.h"

#include "stdint.h"
#include "stdbool.h"

extern state_func_t state_func_setting;

void state_setting_init(void);
void state_setting_enter(void);
void state_setting_update(void);
void state_setting_change_button(uint8_t row, uint8_t col, bool is_pressed);
void state_setting_exit(void);