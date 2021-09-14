#include "midi.h"
#include "bpm.h"
#include "DeviceConfig.h"

#define MIDI_COMMAND_CLOCK (0xF8)
#define MIDI_COMMAND_START (0xFA)
#define MIDI_COMMAND_CONTINUE (0xFB)
#define MIDI_COMMAND_STOP (0xFC)

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

void midi_all_note_off(uint8_t ch) {
    MIDI_EventPacket_t midi_event = (MIDI_EventPacket_t){
        .Event = MIDI_EVENT(0, 0xB0),

        .Data1 = 0xB0 | ch,
        .Data2 = 0x7B,
        .Data3 = 0,
    };
    midi_send_midi_event(&midi_event);
}

void midi_process(MIDI_EventPacket_t event) {
    switch (event.Data1) {
        case MIDI_COMMAND_CLOCK:
            bpm_tick();
            break;
        case MIDI_COMMAND_START:
            bpm_set_midi_started();
            break;
        case MIDI_COMMAND_STOP:
            bpm_set_midi_stopped();
            midi_all_note_off(MIDI_ARP_CHANNEL);
            break;
        default:
            break;
    }
}