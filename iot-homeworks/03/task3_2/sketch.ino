#include "task3_2.h"

int led_pins[] = {11, 10, 9, 6, 5, 3};
LedsLine line(led_pins, SZ, 10);
Joystick joystick(A0, A1, 2, 512, 50);

void setup() {
  line.SetBright(10);
}

void loop() {
  joystick.ReadJoystick(line);
  joystick.CheckButton(line, DEBOUNCE);
  line.UpdateLeds();
  delay(PERIOD);
}
