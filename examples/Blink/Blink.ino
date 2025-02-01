#include "ICHack.h"

/* Program to blink the built-in LED once per second */

/* the setup function runs once when you press reset or power the board */
void setup() {
  /* initialize the logo pins as outputs */
  pinMode(LOGO_I, OUTPUT);
  pinMode(LOGO_C, OUTPUT);
  pinMode(LOGO_H, OUTPUT);
}

/* the loop function runs over and over again forever */
void loop() {
  digitalWrite(LOGO_I, HIGH); /* turn the I on */
  delay(500);                 /* wait for half a second */
  digitalWrite(LOGO_I, LOW);  /* turn the I off */
  delay(500);                 /* wait for half a second */
  digitalWrite(LOGO_C, HIGH);
  delay(500);
  digitalWrite(LOGO_C, LOW);
  delay(500);
  digitalWrite(LOGO_H, HIGH);
  delay(500);
  digitalWrite(LOGO_H, LOW);
  delay(500);
}
