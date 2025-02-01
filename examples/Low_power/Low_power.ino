#include "pico/stdlib.h"
#include "hardware/vreg.h"

// The steps below reduce the current consumption to ~6mA, which is low enough to run on the coin cell.

void setup() {
  vreg_set_voltage(VREG_VOLTAGE_0_90); // Set the core voltage to 0.9V (typically 1.1V)
  delay(2);
  set_sys_clock_khz(18000, false); // Set the CPU frequency to 18MHz (typically 133MHZ) NOTE: USB REQUIRES AT LEAST 48MHZ TO FUNCTION
  delay(2);
}

void loop() {
  delay(1000);
}