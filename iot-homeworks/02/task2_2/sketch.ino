const int DEBOUNCE_TIME = 5;
const int BRIGHT_TIME = 15;

const int pinButton[6] = {12, 13, 10, 11, 8, 9};
const int pinLed[3] = {6, 5, 3};  // красный, зеленый, синий
const int step = 51; // шаг изменения яркости

int lastStateButton[6] = {HIGH, HIGH, HIGH, HIGH, HIGH, HIGH};
int brightsLed[3] = {255, 255, 255};

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

void setup() {
  // Serial.begin(9600);
  for (int i = 0; i < 6; i++) {
    pinMode(pinButton[i], INPUT);
    digitalWrite(pinButton[i], HIGH);
  }

  for (int i = 0; i < 3; i++) {
    pinMode(pinLed[i], OUTPUT);
    analogWrite(pinLed[i], brightsLed[i]);
  }
}

void loop() {
  for (int i = 0; i < 6; i++) {
    int currentState = debounce(i);
    if (lastStateButton[i] == HIGH && currentState == LOW) { // условие нажатия
      if (i & 1) { // нижний ряд кнопок
        dec_brightness(i / 2);
      } else { // верхний ряд кнопок
        inc_brightness(i / 2);
      }
      // Serial.println(brightsLed[i / 2]); 
   }
    lastStateButton[i] = currentState;
  }
  delay(BRIGHT_TIME);
}