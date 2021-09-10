#pragma once
#include <stdint.h>
#include <stdbool.h>

void arp_init(void);
void arp_update(void);

void arp_start(uint8_t row, uint8_t col);
void arp_stop(uint8_t row, uint8_t col);
void arp_clear(void);

void arp_change_pattern(uint8_t no);

void arp_toggle_hold(void);
bool arp_is_in_hold(void);

void arp_restore(void);