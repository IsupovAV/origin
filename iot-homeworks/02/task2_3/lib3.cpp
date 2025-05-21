#include "lib3.h"

int lastStateButton[6] = {HIGH, HIGH, HIGH, HIGH, HIGH, HIGH};
int brightsLed[3] = {255, 255, 255};

// реадизация функций
void init_lib3() {
  for (int i = 0; i < 6; i++) {
    pinMode(pinButton[i], INPUT);
    digitalWrite(pinButton[i], HIGH);
  }

  for (int i = 0; i < 3; i++) {
    pinMode(pinLed[i], OUTPUT);
    analogWrite(pinLed[i], brightsLed[i]);
  }
}

void processing() {
  for (int i = 0; i < 6; i++) {
    int currentState = debounce(i);
    if (lastStateButton[i] == HIGH && currentState == LOW) { // условие нажатия
      if (i & 1) { // нижний ряд кнопок
        dec_brightness(i / 2);
      } else { // верхний ряд кнопок
        inc_brightness(i / 2);
      }
   }
    lastStateButton[i] = currentState;
  }
  delay(BRIGHT_TIME);
}

// увеличить яркость на step
// т. к. подключен anod, то яркость увеличивается
// от минимума 255 до максимума 0
void inc_brightness(int n) {
  if (brightsLed[n] == 0)
    return;
  brightsLed[n] -= step;
  analogWrite(pinLed[n], brightsLed[n]);
}

// уменьшить яркость на step
void dec_brightness(int n) {
  if (brightsLed[n] == 255)
    return;
  brightsLed[n] += step;
  analogWrite(pinLed[n], brightsLed[n]);
}

int debounce(int n) {
  int current = digitalRead(pinButton[n]);
  if (lastStateButton[n] != current) { // если состояние изменилось
    delay(DEBOUNCE_TIME);
    current = digitalRead(pinButton[n]);
  }
  return current;
}
