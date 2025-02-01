#include "ICHack.h"
#include "font.h"

#include <FreeRTOS.h>
#include <task.h>

#define DISPLAY_TASK_STACK_SIZE 10240

void display_update_task(void * pvParameters);
void render();

static uint32_t even_mask = 1431655765;
static uint32_t shift_0_mask = 4281684;
static uint32_t shift_1_mask = 43688;
static uint32_t shift_2_mask = 1360;
static uint32_t shift_3_mask = 160;

static uint32_t col_masks[10] = {
  732576,
  4402592,
  4795808,
  4861344,
  4918688,
  4924832,
  4925856,
  4926624,
  4926752,
  4926848
};

volatile uint32_t *frame_buffer;
uint32_t bit_streams[NUMBER_OF_BIT_STREAMS];

void display_update_task(void * pvParameters) {
  (void) pvParameters;
  delay(500);

  while (true) {
    render();

    // Clear the display so the last column of pixels aren't brighter than the rest
    digitalWrite(rclk, 0);
    digitalWrite(din, 0);
    for (uint8_t i = 0; i < 24; i++) {
      digitalWrite(clk, 0);
      digitalWrite(clk, 1);
    }
    digitalWrite(rclk, 1);

    delay(10);
  }
}

void display_init(volatile uint32_t* fb){
  frame_buffer = fb;
  digitalWrite(5, HIGH);
  for (uint8_t i = 0; i < FRAME_BUFFER_WIDTH; i++) {
    frame_buffer[i] = 0;
  }

  for (uint8_t i = 0; i < NUMBER_OF_BIT_STREAMS; i++) {
    bit_streams[i] = 0;
  }

  pinMode(clk, OUTPUT);
  pinMode(rclk, OUTPUT);
  pinMode(oe, OUTPUT);
  pinMode(din, OUTPUT);

  analogWriteFreq(1000000);
  analogWriteResolution(8);
  analogWrite(oe, DEFAULT_BRIGHTNESS);

  TaskHandle_t display_task_handle = NULL;

  xTaskCreate(display_update_task,     /* Function that implements the task. */
              "DISPLAY",               /* Text name for the task. */
              DISPLAY_TASK_STACK_SIZE, /* Stack size in words, not bytes. */
              nullptr,                 /* Parameter passed into the task. */
              1,                       /* Priority at which the task is created. */
              &display_task_handle);   /* Used to pass out the created task's handle. */
  
  vTaskCoreAffinitySet(display_task_handle, 1 << 1);
}

void display_clear(){
  for (uint8_t i = 0; i < FRAME_BUFFER_WIDTH; i++) {
    frame_buffer[i] = 0;
  }
}

void frame_buffer_to_bit_streams(volatile uint32_t* frame_buffer, uint32_t* bit_streams) {
  uint32_t tmp;

  for (uint8_t col = 0; col < NUMBER_OF_BIT_STREAMS; col++) {

    if (col < 5) {
      tmp = frame_buffer[4 - col] & even_mask;
    } else {
      tmp = (frame_buffer[col - 5] >> 1) & even_mask;
    }

    tmp = (tmp & ~shift_0_mask) | ((tmp & shift_0_mask) >> 1);
    tmp = (tmp & ~shift_1_mask) | ((tmp & shift_1_mask) >> 1);
    tmp = (tmp & ~shift_2_mask) | ((tmp & shift_2_mask) >> 1);
    tmp = (tmp & ~shift_3_mask) | ((tmp & shift_3_mask) >> 1);

    bit_streams[col] = tmp | col_masks[col];
  }
}

void render(){

  frame_buffer_to_bit_streams(frame_buffer, bit_streams);

    for (uint8_t i = 0; i < NUMBER_OF_BIT_STREAMS; i++) {

      digitalWrite(rclk, 0);

      for (uint8_t shift = 0; shift < 24; shift++) {
        digitalWrite(clk, 0);
        digitalWrite(din, (bit_streams[i] >> shift) & 1);
        digitalWrite(clk, 1);
      }

      digitalWrite(rclk, 1);

      delay(1);
    }
}

void display_set_brightness(uint8_t brightness){
  analogWrite(oe, brightness);
}

void display_draw_char(char c, int32_t y) {

  if (y < 0) {
    return;
  }

  const uint8_t* char_mask;
  
  if (c >= 'A' && c <= 'Z') {
    char_mask = CHARACTER_MAPPING[c - 'A'];
  }

  else if (c >= 'a' && c <= 'z') {
    char_mask = CHARACTER_MAPPING[c - 'a'];
  }

  else if (c >= '0' && c <= '9') {
    char_mask = INTEGER_MAPPING[c - '0'];
  }

  else if (c >= '\200') {
      char_mask = SPECIAL_CHARS[c - '\200'];
  }

  else {
    uint8_t index = 0; // index = 0 means a space or unknown character will be a space
    switch (c)
    {
    case '/':
        index = 1;
        break;
    case '\\':
        index = 2;
        break;
    case '>':
        index = 3;
        break;
    case '<':
        index = 4;
        break;
    case ':':
        index = 5;
        break;
    case '|':
        index = 6;
        break;
    case '!':
        index = 7;
        break;
    case '(':
        index = 8;
        break;
    case ')':
        index = 9;
        break;
    case '-':
        index = 10;
        break;
    case '+':
        index = 10;
        break;
    case '.':
        index = 12;
        break;
    case '\'':
        index = 13;
        break;
    case '?':
        index = 14;
        break;
    default:
        break;
    }
    char_mask = PUNCTUATION[index];
  }

  for (uint8_t col = 0; col < CHARACTER_HEIGHT; col++) {
    frame_buffer[col] |= (y - CHARACTER_WIDTH + 1) < 0 ? char_mask[col] >> (-y + CHARACTER_WIDTH - 1) : char_mask[col] << (y - CHARACTER_WIDTH + 1);
  }
}

void display_draw_string(char *s, uint8_t length, int32_t y) {
  for (uint8_t i = 0; i < length; i++) {
    display_draw_char(s[i], y - i * (CHARACTER_WIDTH + 1));
  }
}
