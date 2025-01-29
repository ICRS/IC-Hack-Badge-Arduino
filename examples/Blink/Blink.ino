/* Program to blink the built-in LED once per second */

/* the setup function runs once when you press reset or power the board */
void setup() {
  /* initialize LED_BUILTIN pin as an output */
  pinMode(LED_BUILTIN, OUTPUT);
}

/* the loop function runs over and over again forever */
void loop() {
  digitalWrite(LED_BUILTIN, HIGH); /* turn the LED on */
  delay(500);                      /* wait for half a second */
  digitalWrite(LED_BUILTIN, LOW);  /* turn the LED off */
  delay(500);                      /* wait for half a second */
}
