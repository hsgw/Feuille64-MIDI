/*   Copyright 2021 Takuya Urakawa (hsgw) */

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

void matrix_button_changed(uint8_t row, uint8_t col, bool is_pressed) { context_change_button(row, col, is_pressed); }

/** Main program entry point. This routine contains the overall program flow,
 * including initial setup of all components and the main program loop.
 */
int main(void) {
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
        MIDI_EventPacket_t ReceivedMIDIEvent;
        while (MIDI_Device_ReceiveEventPacket(&Keyboard_MIDI_Interface, &ReceivedMIDIEvent)) {
            midi_process(ReceivedMIDIEvent);
        }

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
