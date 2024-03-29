/* Copyright 2021 QMK
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#pragma once

#include <avr/io.h>

#define PORT_SHIFTER 4  // this may be 4 for all AVR chips

// If you want to add more to this list, reference the PINx definitions in these
// header files:
// https://github.com/vancegroup-mirrors/avr-libc/tree/master/avr-libc/include/avr

#define ADDRESS_BASE 0x00
#define PINB_ADDRESS 0x3
#define PINC_ADDRESS 0x6
#define PIND_ADDRESS 0x9
#define PINE_ADDRESS 0xC
#define PINF_ADDRESS 0xF

#define PINDEF(port, pin) ((PIN##port##_ADDRESS << PORT_SHIFTER) | pin)

#define _PIN_ADDRESS(p, offset) _SFR_IO8(ADDRESS_BASE + ((p) >> PORT_SHIFTER) + (offset))
// Port X Input Pins Address
#define PINx_ADDRESS(p) _PIN_ADDRESS(p, 0)
// Port X Data Direction Register,  0:input 1:output
#define DDRx_ADDRESS(p) _PIN_ADDRESS(p, 1)
// Port X Data Register
#define PORTx_ADDRESS(p) _PIN_ADDRESS(p, 2)

/* I/O pins */
#define B0 PINDEF(B, 0)
#define B1 PINDEF(B, 1)
#define B2 PINDEF(B, 2)
#define B3 PINDEF(B, 3)
#define B4 PINDEF(B, 4)
#define B5 PINDEF(B, 5)
#define B6 PINDEF(B, 6)
#define B7 PINDEF(B, 7)

#define C0 PINDEF(C, 0)
#define C1 PINDEF(C, 1)
#define C2 PINDEF(C, 2)
#define C3 PINDEF(C, 3)
#define C4 PINDEF(C, 4)
#define C5 PINDEF(C, 5)
#define C6 PINDEF(C, 6)
#define C7 PINDEF(C, 7)

#define D0 PINDEF(D, 0)
#define D1 PINDEF(D, 1)
#define D2 PINDEF(D, 2)
#define D3 PINDEF(D, 3)
#define D4 PINDEF(D, 4)
#define D5 PINDEF(D, 5)
#define D6 PINDEF(D, 6)
#define D7 PINDEF(D, 7)

#define E0 PINDEF(E, 0)
#define E1 PINDEF(E, 1)
#define E2 PINDEF(E, 2)
#define E3 PINDEF(E, 3)
#define E4 PINDEF(E, 4)
#define E5 PINDEF(E, 5)
#define E6 PINDEF(E, 6)
#define E7 PINDEF(E, 7)

#define F0 PINDEF(F, 0)
#define F1 PINDEF(F, 1)
#define F2 PINDEF(F, 2)
#define F3 PINDEF(F, 3)
#define F4 PINDEF(F, 4)
#define F5 PINDEF(F, 5)
#define F6 PINDEF(F, 6)
#define F7 PINDEF(F, 7)
