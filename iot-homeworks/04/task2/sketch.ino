#include <fDigitsSegtPin.h> // Подключаем библиотеку fDigitsSegtPin

#define start_stop 0
#define reset A0

// Инициализируем объект-4-х разрядный индикатор, передаём использованные
// для подключения контакты на:
fDigitsSegtPin Display(6, 5, 9, 4, 8, 13, 3, 12, 11, 7, 2, 10);

int last_start = LOW;
int last_reset = LOW;
bool is_stopped = true;

void setup() {
  Display.begin();
  
  pinMode(start_stop, INPUT_PULLUP);
  pinMode(reset, INPUT_PULLUP);
  digitalWrite(start_stop, HIGH);
  digitalWrite(reset, HIGH);
}

int debounce(int button, int last) {
  int current = digitalRead(button);

  if (last != current) {
    delay(5);
    current = digitalRead(button);
  }
  return current;
}

void loop() {
  static unsigned long timer = millis();  //текущее время
  static int seconds = 0;               //время, отображаемое на индикаторе

  int current = debounce(reset, last_reset);

  if (last_reset == HIGH && current == LOW && is_stopped) {
    seconds = 0;
  }
  last_reset = current;

  current = debounce(start_stop, last_start);
  if(last_start == HIGH && current == LOW){
    is_stopped = !is_stopped;
  }
  last_start = current;

  if (millis() - timer >= 1000 && !is_stopped) {
    timer = millis();
    ++seconds;
  }
  
  Display.print(seconds);
}

