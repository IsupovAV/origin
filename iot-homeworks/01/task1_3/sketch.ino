const int num_out = 10; // сделал на 10 сегментов
const int num_tm = 4;   // число интервалов

const int ledPins[] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11}; // пины линейки
const int tm_delay[] = {1000, 500, 250, 100}; // интервалы задержек
const int slick_delay = 50; // добавил для большей плавности
void setup() {
  for (int i = 0; i < num_out; ++i) {
    pinMode(ledPins[i], OUTPUT);
  }
}

void loop() {
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < num_out; ++j) {
      digitalWrite(ledPins[j], HIGH); // вкл. сегмент
      delay(tm_delay[i]);
      digitalWrite(ledPins[j], LOW); // выкл. сегмент
      // Небольшая задержка. На моем компе при появлении
      // нового сегмента, старый при маленьких задержках
      // не успевает стереться
      delay(slick_delay); // небольшая задержка 
    }
  }
}