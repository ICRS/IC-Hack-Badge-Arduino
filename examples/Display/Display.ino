#include "ICHack.h"

volatile uint32_t fb[FRAME_BUFFER_WIDTH];

void setup() {
  display_init(fb);
  delay(1000);
}

void loop() {
  display_clear();
  display_draw_char('I', 19);
  delay(1000);
  display_draw_char('C', 14);
  delay(1000);
  display_draw_char('H', 9);
  delay(1000);
  display_clear();
  delay(1000);

  char message[] = "HELLO WORLD";
  for (uint8_t i = 0; i < 100; i++) {
    display_clear();
    display_draw_string(message, 11, i);
    delay(100);
  }

  delay(1000);
}
