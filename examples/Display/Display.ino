#include "ICHack.h"

// Create the frame buffer. The first 24 bits of each uint32_t
// represent one column of the LED matrix. You can write to this
// buffer directly and patters will appear on the display.
volatile uint32_t fb[FRAME_BUFFER_WIDTH];

void setup() {

  // Initialise the display by passing it the frame buffer. This
  // will create a thread that continuously renders the frame
  // buffer to the matrix.
  display_init(fb);
  delay(1000);
}

void loop() {
  display_clear(); // Clear the display
  display_draw_char('I', 19); // Write an I character with an offset of 19
  delay(1000);
  display_draw_char('C', 14);
  delay(1000);
  display_draw_char('H', 9);
  delay(1000);
  display_clear();
  delay(1000);

  // Scroll the text "HELLO WORLD" down the display
  char message[] = "HELLO WORLD";
  for (uint8_t i = 0; i < 100; i++) {
    display_clear();
    display_draw_string(message, 11, i);
    delay(100);
  }

  delay(1000);
}
