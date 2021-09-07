#pragma once
#include "stdint.h"
#include "stdbool.h"

typedef enum { STATE_MAIN = 0, STATE_PATTERN, STATE_VELO, STATE_SETTING } state_t;

typedef struct {
    void (*init)(void);
    void (*enter)(void);
    void (*update)(void);
    void (*change_button)(uint8_t row, uint8_t col, bool is_pressed);
    void (*exit)(void);
} state_func_t;

void context_init(void);
void context_update(void);
void context_change_button(uint8_t row, uint8_t col, bool is_pressed);
void context_change_state(state_t next);