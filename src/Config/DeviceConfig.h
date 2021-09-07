#pragma once

// USB descriptor setting
#define USB_VID 0x1234
#define USB_PID 0x0001
#define USB_MANUFACTURER_NAME L"feuille64"
#define USB_DEVICE_NAME L"feuille64"
#define USB_SERIAL_NUMBER L"m9001230"
// #define USB_SERIAL_NUMBER L"a40h-002"

// matrix pin out
#define MATRIX_COLS 8
#define MATRIX_ROWS 9
#define MATRIX_COL_PINS \
    { F1, F4, F5, F6, F7, B3, B1, B2 }
#define MATRIX_ROW_PINS \
    { D0, C7, C6, B6, B5, B4, D7, D6, D4 }

// debounce time in ms
#define DEBOUNCE 5

// col order in matrix.c
#define COL_ORDER \
    { 0, 1, 2, 3, 4, 6, 7, 5 }

// ws2812 pin setting
#define ws2812_port F
#define ws2812_pin 0

// LEDs
#define LED_ROW 8
#define LED_COL 8
#define LED_COUNT (LED_ROW * LED_COL)

// ms
#define LED_UPDATE_INTERVAL 20

#define LED_COLOR_R 32
#define LED_COLOR_G 32
#define LED_COLOR_B 32

// clang-format off
#define LED_ORDER \
    { 0,  1,  2,  3,  4,  5,  6,  7, \
     15, 14, 13, 12, 11, 10,  9,  8, \
     16, 17, 18, 19, 20, 21, 22, 23, \
     31, 30, 29, 28, 27, 26, 25, 24, \
     32, 33, 34, 35, 36, 37, 38, 39, \
     47, 46, 45, 44, 43, 42, 41, 40, \
     48, 49, 50, 51, 52, 53, 54, 55, \
     63, 62, 61, 60, 59, 58, 57, 56 }
// clang-format on

#define MIDI_ARP_CHANNEL (1)