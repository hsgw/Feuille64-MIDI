/*   Copyright 2021 Takuya Urakawa (hsgw)
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

#pragma once

#include <stdint.h>
#include <stdbool.h>

#include <LUFA/Drivers/USB/USB.h>
#include <LUFA/Platform/Platform.h>

void midi_init(void);
void midi_send_midi_event(MIDI_EventPacket_t* midi_event);
void midi_send_note(bool on, uint8_t note, uint8_t velocity, uint8_t ch);

void midi_all_note_off(uint8_t ch);

void midi_process(MIDI_EventPacket_t event);