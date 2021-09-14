/*   Copyright 2021 Takuya Urakawa (hsgw), QMK
 *
 *   This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 2 of the License, or
 *   (at your option) any later version.

 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include "encoder.h"
#include "gpio.h"
#include "debounce.h"

#define ENCODER_NUM 3
#define ENCODER_PIN PIND
#define ENCODER_PORT PORTD
#define ENCODER_DDR DDRD
#define ENCODER_MASK (_BV(1) + _BV(2) + _BV(3))

#define ENCODER_RESOLUTION 4

static const int8_t encoder_LUT[] = {0, -1, 1, 0, 1, 0, 0, -1, -1, 0, 0, 1, 0, 1, -1, 0};

uint8_t encoder_states[3];
int8_t  encoder_pulses[3];

void encoder_read(void) {
    uint8_t current_pin[3] = {readPin(D1), readPin(D2), readPin(D3)};

    encoder_states[0] = encoder_states[0] << 2;
    encoder_states[0] |= current_pin[0] | (current_pin[1] << 1);
    encoder_states[1] = encoder_states[1] << 2;
    encoder_states[1] |= current_pin[1] | (current_pin[2] << 1);
    encoder_states[2] = encoder_states[2] << 2;
    encoder_states[2] |= current_pin[2] | (current_pin[0] << 1);
}

void encoder_init(void) {
    setPinInputHigh(D1);
    setPinInputHigh(D2);
    setPinInputHigh(D3);

    _delay_ms(1);

    encoder_read();
}

void encoder_update(void) {
    encoder_read();

    for (uint8_t i = 0; i < ENCODER_NUM; i++) {
        encoder_pulses[i] += encoder_LUT[encoder_states[i]];
        if (encoder_pulses[i] >= ENCODER_RESOLUTION) {
            encoder_changed(i, true);
        } else if (encoder_pulses[i] <= -ENCODER_RESOLUTION) {
            encoder_changed(i, false);
        }
        encoder_pulses[i] %= ENCODER_RESOLUTION;
    }
}

void __attribute__((weak)) encoder_changed(uint8_t index, bool clockwise) {}