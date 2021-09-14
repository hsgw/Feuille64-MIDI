#pragma once
#include "context.h"

#include "stdint.h"
#include "stdbool.h"

extern state_func_t state_func_velocity;

void state_velocity_init(void);
void state_velocity_enter(void);
void state_velocity_update(void);
void state_velocity_change_button(uint8_t row, uint8_t col, bool is_pressed);
void state_velocity_exit(void);
