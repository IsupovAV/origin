const int pinLed[] = {8, 9, 10}; // пины rgb-led
const int pinButton = 2;
const int BOUNCE_TIME = 5;  // задержка "дребезга"
const int NUM_STATES = 8;   // число сотояний rgb-led
const int BLINK_TIME = 50;  // задержка для сглаживания мерцания

int lastStatus = LOW; // предыдущее состояние кнопки
int counter = 0;      // счетчик нажатий

// Функция подавления дребезга
// last - предыдущее состояние кнопки
int debounce (int last) {
  int current = digitalRead(pinButton);
  if (last != current) { //если состояние изменилось
    delay(BOUNCE_TIME);
    current = digitalRead(pinButton);
  }
  return current;
}

void segments_on_off(int n, int on_off) {
  if (n & 1) digitalWrite(pinLed[0], on_off);
  if (n & 2) digitalWrite(pinLed[1], on_off);
  if (n & 4) digitalWrite(pinLed[2], on_off);
  delay(BLINK_TIME);
}

void setup() {
  for (int i = 0; i < 3; ++i) {
    pinMode(pinLed[i], OUTPUT);
    digitalWrite(pinLed[i], HIGH);  // выключение сегментов (анод)
  }
  pinMode(pinButton, INPUT);
  digitalWrite(pinButton, HIGH);
}

void loop() {
  int currStatus = debounce (lastStatus);
  if (lastStatus == HIGH && currStatus == LOW) { //условие нажатия
    segments_on_off(counter, HIGH);   // выключение сегментов
    counter = ++counter % NUM_STATES;
    segments_on_off(counter, LOW);    // включение сегментов
  }
  lastStatus = currStatus;
}

