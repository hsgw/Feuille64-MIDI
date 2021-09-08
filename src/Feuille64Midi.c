/*
             LUFA Library
     Copyright (C) Dean Camera, 2021.

  dean [at] fourwalledcubicle [dot] com
           www.lufa-lib.org
*/

/*
  Copyright 2021  Dean Camera (dean [at] fourwalledcubicle [dot] com)

  Permission to use, copy, modify, distribute, and sell this
  software and its documentation for any purpose is hereby granted
  without fee, provided that the above copyright notice appear in
  all copies and that both that the copyright notice and this
  permission notice and warranty disclaimer appear in supporting
  documentation, and that the name of the author not be used in
  advertising or publicity pertaining to distribution of the
  software without specific, written prior permission.

  The author disclaims all warranties with regard to this
  software, including all implied warranties of merchantability
  and fitness.  In no event shall the author be liable for any
  special, indirect or consequential damages or any damages
  whatsoever resulting from loss of use, data or profits, whether
  in an action of contract, negligence or other tortious action,
  arising out of or in connection with the use or performance of
  this software.
*/

/** \file
 *
 *  Main source file for the MIDI demo. This file contains the main tasks of
 *  the demo and is responsible for the initial application hardware
 * configuration.
 */

#include "Feuille64Midi.h"
#include "qmk/gpio.h"
#include "qmk/timer.h"
#include "qmk/matrix.h"
// #include "qmk/encoder.h"
#include "leds.h"
#include "bpm.h"
#include "midi.h"

#include "context.h"

/** LUFA MIDI Class driver interface configuration and state information. This
 * structure is passed to all MIDI Class driver functions, so that multiple
 * instances of the same class within a device can be differentiated from one
 * another.
 */
USB_ClassInfo_MIDI_Device_t Keyboard_MIDI_Interface = {
    .Config =
        {
            .StreamingInterfaceNumber = INTERFACE_ID_AudioStream,
            .DataINEndpoint =
                {
                    .Address = MIDI_STREAM_IN_EPADDR,
                    .Size    = MIDI_STREAM_EPSIZE,
                    .Banks   = 1,
                },
            .DataOUTEndpoint =
                {
                    .Address = MIDI_STREAM_OUT_EPADDR,
                    .Size    = MIDI_STREAM_EPSIZE,
                    .Banks   = 1,
                },
        },
};

void matrix_button_changed(uint8_t row, uint8_t col, bool is_pressed) {
    context_change_button(row, col, is_pressed);
    // uint8_t midi_command = (is_pressed ? MIDI_COMMAND_NOTE_ON : MIDI_COMMAND_NOTE_OFF);

    // MIDI_EventPacket_t MIDIEvent = (MIDI_EventPacket_t){
    //     .Event = MIDI_EVENT(0, midi_command),

    //     .Data1 = midi_command | 1,
    //     .Data2 = 0x30 + row * 8 + col,
    //     .Data3 = MIDI_STANDARD_VELOCITY,
    // };

    // MIDI_Device_SendEventPacket(&Keyboard_MIDI_Interface, &MIDIEvent);
    // MIDI_Device_Flush(&Keyboard_MIDI_Interface);
}

// #define CC_NUM 3
// #define CC_NO 12
// uint8_t encoder_values[CC_NUM];

// void encoder_changed(uint8_t no, bool clockwise) {
//     uint8_t midi_command = MIDI_COMMAND_CONTROL_CHANGE;

//     if (!clockwise && encoder_values[no] > 0) {
//         encoder_values[no]--;
//     }

//     if (clockwise && encoder_values[no] < 127) {
//         encoder_values[no]++;
//     }

//     MIDI_EventPacket_t MIDIEvent = (MIDI_EventPacket_t){
//         .Event = MIDI_EVENT(0, midi_command),

//         .Data1 = midi_command | 1,
//         .Data2 = no,
//         .Data3 = encoder_values[no],
//     };
//     MIDI_Device_SendEventPacket(&Keyboard_MIDI_Interface, &MIDIEvent);
//     MIDI_Device_Flush(&Keyboard_MIDI_Interface);
// }

void midi_process() {}

/** Main program entry point. This routine contains the overall program flow,
 * including initial setup of all components and the main program loop.
 */
int main(void) {
    bool led_flag = false;
    SetupHardware();
    GlobalInterruptEnable();

    context_init();
    context_enter();

    uint16_t leds_last_update = timer_read();

    for (;;) {
        uint16_t current_time = timer_read();

        matrix_update();
        // encoder_update();
        context_update();
        // MIDI_EventPacket_t ReceivedMIDIEvent;
        // while (MIDI_Device_ReceiveEventPacket(&Keyboard_MIDI_Interface, &ReceivedMIDIEvent)) {
        //     // if ((ReceivedMIDIEvent.Event == MIDI_EVENT(0, MIDI_COMMAND_NOTE_ON)) && (ReceivedMIDIEvent.Data3 > 0))
        //     // LEDs_SetAllLEDs(ReceivedMIDIEvent.Data2 > 64 ? LEDS_LED1 : LEDS_LED2);
        // }

        MIDI_Device_USBTask(&Keyboard_MIDI_Interface);

        if (timer_elapsed(leds_last_update) >= LED_UPDATE_INTERVAL) {
            leds_update();
            leds_last_update = current_time;
        }
    }
}

/** Configures the board hardware and chip peripherals for the demo's
 * functionality. */
void SetupHardware(void) {
    /* Disable watchdog if enabled by bootloader/fuses */
    MCUSR &= ~(1 << WDRF);
    wdt_disable();

    /* Disable JTAG */
    MCUCR |= _BV(JTD);
    MCUCR |= _BV(JTD);

    /* Disable clock division */
    clock_prescale_set(clock_div_1);

    /* Hardware Initialization */
    timer_init();
    bpm_init();
    leds_init();
    matrix_init();
    // encoder_init();
    USB_Init();
    midi_init();
}

/** Checks for changes in the position of the board joystick, sending MIDI
 * events to the host upon each change. */
// void CheckJoystickMovement(void) {
//     static uint8_t PrevJoystickStatus;

//     uint8_t MIDICommand = 0;
//     uint8_t MIDIPitch;

//     /* Get current joystick mask, XOR with previous to detect joystick changes */
//     uint8_t JoystickStatus  = Joystick_GetStatus();
//     uint8_t JoystickChanges = (JoystickStatus ^ PrevJoystickStatus);

//     /* Get board button status - if pressed use channel 10 (percussion), otherwise
//      * use channel 1 */
//     uint8_t Channel = ((Buttons_GetStatus() & BUTTONS_BUTTON1) ? MIDI_CHANNEL(10) : MIDI_CHANNEL(1));

//     if (JoystickChanges & JOY_LEFT) {
//         MIDICommand = ((JoystickStatus & JOY_LEFT) ? MIDI_COMMAND_NOTE_ON : MIDI_COMMAND_NOTE_OFF);
//         MIDIPitch   = 0x3C;
//     }

//     if (JoystickChanges & JOY_UP) {
//         MIDICommand = ((JoystickStatus & JOY_UP) ? MIDI_COMMAND_NOTE_ON : MIDI_COMMAND_NOTE_OFF);
//         MIDIPitch   = 0x3D;
//     }

//     if (JoystickChanges & JOY_RIGHT) {
//         MIDICommand = ((JoystickStatus & JOY_RIGHT) ? MIDI_COMMAND_NOTE_ON : MIDI_COMMAND_NOTE_OFF);
//         MIDIPitch   = 0x3E;
//     }

//     if (JoystickChanges & JOY_DOWN) {
//         MIDICommand = ((JoystickStatus & JOY_DOWN) ? MIDI_COMMAND_NOTE_ON : MIDI_COMMAND_NOTE_OFF);
//         MIDIPitch   = 0x3F;
//     }

//     if (JoystickChanges & JOY_PRESS) {
//         MIDICommand = ((JoystickStatus & JOY_PRESS) ? MIDI_COMMAND_NOTE_ON : MIDI_COMMAND_NOTE_OFF);
//         MIDIPitch   = 0x3B;
//     }

//     if (MIDICommand) {
//         MIDI_EventPacket_t MIDIEvent = (MIDI_EventPacket_t){
//             .Event = MIDI_EVENT(0, MIDICommand),

//             .Data1 = MIDICommand | Channel,
//             .Data2 = MIDIPitch,
//             .Data3 = MIDI_STANDARD_VELOCITY,
//         };

//         MIDI_Device_SendEventPacket(&Keyboard_MIDI_Interface, &MIDIEvent);
//         MIDI_Device_Flush(&Keyboard_MIDI_Interface);
//     }

//     PrevJoystickStatus = JoystickStatus;
// }

/** Event handler for the library USB Connection event. */
void EVENT_USB_Device_Connect(void) {}

/** Event handler for the library USB Disconnection event. */
void EVENT_USB_Device_Disconnect(void) {}

/** Event handler for the library USB Configuration Changed event. */
void EVENT_USB_Device_ConfigurationChanged(void) {
    bool ConfigSuccess = true;

    ConfigSuccess &= MIDI_Device_ConfigureEndpoints(&Keyboard_MIDI_Interface);
}

/** Event handler for the library USB Control Request reception event. */
void EVENT_USB_Device_ControlRequest(void) { MIDI_Device_ProcessControlRequest(&Keyboard_MIDI_Interface); }
