#pragma once
#include <stdint.h>

void arp_init(void);
void arp_update(void);

void arp_start(uint8_t row, uint8_t col);
void arp_stop(uint8_t row, uint8_t col);