#ifndef ICHACK_H
#define ICHACK_H

#include "Arduino.h"

// Logo pins
static const uint8_t LOGO_I = 6;
static const uint8_t LOGO_C = 5;
static const uint8_t LOGO_H = 4;

// Input pins
static const uint8_t BUTTON_X = 2;
static const uint8_t BUTTON_y = 0;
static const uint8_t BUTTON_A = 3;
static const uint8_t BUTTON_B = 1;

// Display macros
#define FRAME_BUFFER_WIDTH 5
#define FRAME_BUFFER_HEIGHT 24
#define NUMBER_OF_BIT_STREAMS 10
#define DEFAULT_BRIGHTNESS 180

// Display pins
static const uint8_t clk = 17;
static const uint8_t rclk = 18;
static const uint8_t oe = 16;
static const uint8_t din = 15;

// Display functions
void display_init(volatile uint32_t fb[]);
void display_set_brightness(uint8_t brightness);
void display_clear();
void display_draw_char(char c, int32_t y);
void display_draw_string(char *s, uint8_t length, int32_t y);

#endif