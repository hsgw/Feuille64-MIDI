#include "leds.h"
#include "Config/DeviceConfig.h"
#include "light_ws2812/light_ws2812.h"

static struct cRGB leds_rgb[LED_COUNT];

inline struct cRGB rgb_create(uint8_t r, uint8_t g, uint8_t b) {
    struct cRGB rgb;
    rgb.r = r;
    rgb.g = g;
    rgb.b = b;
    return rgb;
}

inline struct cRGB rgb_create_brightness(uint8_t brightness) {
    struct cRGB rgb;
    rgb.r = LED_COLOR_R / 16 * brightness;
    rgb.g = LED_COLOR_G / 16 * brightness;
    rgb.b = LED_COLOR_B / 16 * brightness;
    return rgb;
}

void leds_init(void) {
    for (uint8_t i = 0; i < LED_COUNT; i++) {
        leds_rgb[i] = rgb_create(0, 0, 0);
    }
}

void leds_update(void) { ws2812_setleds(leds_rgb, LED_COUNT); }

void leds_set_rgb(uint8_t row, uint8_t col, uint8_t r, uint8_t g, uint8_t b) { leds_rgb[LED_COL * row + (row % 2 == 0 ? col : LED_COL - 1 - col)] = rgb_create(r, g, b); }

void leds_set(uint8_t row, uint8_t col, uint8_t brightness) { leds_rgb[LED_COL * row + (row % 2 == 0 ? col : LED_COL - 1 - col)] = rgb_create_brightness(brightness); }

void leds_set_all(uint8_t brightness) {
    for (int8_t row = 0; row < LED_ROW; row++) {
        for (int8_t col = 0; col < LED_COL; col++) {
            leds_set(row, col, brightness);
        }
    }
}