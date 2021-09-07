#include "midi.h"

extern USB_ClassInfo_MIDI_Device_t Keyboard_MIDI_Interface;

void midi_init(void) {}

void midi_send_midi_event(MIDI_EventPacket_t* midi_event) {
    MIDI_Device_SendEventPacket(&Keyboard_MIDI_Interface, midi_event);
    MIDI_Device_Flush(&Keyboard_MIDI_Interface);
}

void midi_send_note(bool on, uint8_t note, uint8_t velocity, uint8_t ch) {
    uint8_t midi_command = on ? MIDI_COMMAND_NOTE_ON : MIDI_COMMAND_NOTE_OFF;

    MIDI_EventPacket_t midi_event = (MIDI_EventPacket_t){
        .Event = MIDI_EVENT(0, midi_command),

        .Data1 = midi_command | ch,
        .Data2 = note,
        .Data3 = velocity,
    };
    midi_send_midi_event(&midi_event);
}