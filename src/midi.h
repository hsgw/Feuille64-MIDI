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