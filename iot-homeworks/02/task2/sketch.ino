const int pinButton[6] = {8, 9, 10, 11, 12, 13};
const int pinLed[3] = {3, 5, 6};
const int step = 50;

int lastStateButton[6] = {HIGH, HIGH, HIGH, HIGH, HIGH, HIGH};
int brightsLed[3] = {250, 250, 250};

void setup() {
  for (int i = 0; i < 6; i++) {
    pinMode(pinButton[i], INPUT);
    digitalWrite(pinButton[i], 250);
  }

  for (int i = 0; i < 3; i++) {
    pinMode(pinLed[i], OUTPUT);
    digitalWrite(pinLed[i], HIGH);
  }
}

void loop() {
  for (int i = 0; i < 6; i++) {
    int currentState = debounce(i);
    if (lastStateButton[i] == HIGH && currentState == LOW) { //условие нажатия
      if (i % 2) {
        dec_brightness(i / 2);
      } else {
        inc_brightness(i / 2);
      }
    }
    lastStateButton[i] = currentState;
  }
}

void inc_brightness(int n) {
  if (brightsLed[n] == 0) return;
  brightsLed[n] -= step;
  analogWrite(pinLed[n], brightsLed[n]);
  delay(10);
}

void dec_brightness(int n) {
  if (brightsLed[n] == 250) return;
  brightsLed[n] += step;
  analogWrite(pinLed[n], brightsLed[n]);
  delay(10);
}

int debounce(int n) {
  int current = digitalRead(pinButton[n]);
  if (lastStateButton[n] != current) { // если состояние изменилось
    delay(5);
    current = digitalRead(pinButton[n]);
  }
  return current;
}

