#pragma once

#include "DeviceConfig.h"
#include <stdint.h>
#include <stdbool.h>

#define VELOCITY_STEP (5)

static const uint8_t VELOCITY_TABLE[VELOCITY_STEP] = {16, 32, 64, 100, 127};

typedef struct {
    int8_t  row;
    int8_t  col;
    uint8_t vel;
    bool    enable;
} step_t;

typedef struct {
    step_t  steps[PATTERN_STEP_MAX];
    uint8_t length;
} pattern_t;

void    pattern_init(void);
step_t  pattern_next_step(uint8_t* step_count);
void    pattern_change(uint8_t pattern);
uint8_t pattern_get_current(void);
step_t  pattern_get_step(uint8_t step_count);
uint8_t pattern_get_length(void);

void pattern_set_step(uint8_t step, uint8_t row, uint8_t col);
void pattern_set_velocity(uint8_t step, uint8_t velocity);
void pattern_set_length(uint8_t length);
void pattern_toggle_enable(uint8_t step);