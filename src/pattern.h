#pragma once

#include <stdint.h>
#include "DeviceConfig.h"

typedef struct {
    int8_t  row;
    int8_t  col;
    uint8_t vel;
} step_t;

typedef struct {
    step_t  steps[PATTERN_STEP_MAX];
    uint8_t length;
} pattern_t;

void    pattern_init(void);
step_t  pattern_get_step(uint8_t* step_count);
void    pattern_change(uint8_t no);
uint8_t pattern_get_current();
void    pattern_edit_begin(uint8_t no);
void    pattern_edit_begin_current(void);
void    pattern_edit_step(uint8_t row, uint8_t col);
void    pattern_edit_end(void);