#include <fDigitsSegtPin.h> // Подключаем библиотеку fDigitsSegtPin

#define TIME_DEBOUNCE 5

const int start_stop = 0; // пин кнопки старт/стоп
const int reset = A0;     // пин кнопки сброс

// Инициализируем объект-4-х разрядный индикатор, передаём использованные
// для подключения контсруктору
fDigitsSegtPin Display(6, 5, 9, 4, 8, 13, 3, 12, 11, 7, 2, 10);

int last_start = LOW;   // состояния кнопок
int last_reset = LOW;
bool is_stopped = true; // признак остановки, нужен чтобы выполнить условия задачи

// программное подавление дребезга
int debounce(int button, int last) {
  int current = digitalRead(button);

  if (last != current) {
    delay(TIME_DEBOUNCE);
    current = digitalRead(button);
  }
  return current;
}

void setup() {
  Display.begin();
  Display.doPrint_firstZero = 1;  // включить лидирующий ноль
  // первоначальная настройка кнопок
  pinMode(start_stop, INPUT_PULLUP);
  pinMode(reset, INPUT_PULLUP);
  digitalWrite(start_stop, HIGH);
  digitalWrite(reset, HIGH);
}

void loop() {
  static unsigned long timer = millis();//текущее время
  static int seconds = 0;               //время, отображаемое на индикаторе

  int current = debounce(reset, last_reset);

  if (last_reset == HIGH && current == LOW && is_stopped) {
    seconds = 0;
  }
  last_reset = current;

  current = debounce(start_stop, last_start);
  if (last_start == HIGH && current == LOW) {
    is_stopped = !is_stopped;
  }
  last_start = current;

  if (millis() - timer >= 1000 && !is_stopped) {
    timer = millis();
    ++seconds;
  }

  Display.print(seconds);
}

