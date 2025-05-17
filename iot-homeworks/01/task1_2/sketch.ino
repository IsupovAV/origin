const int num_out = 10; // сделал на 10 сегментов
int const up_time = 500; // задержка при движении снизу вверх
int const down_time = 1000; // задержка при движении сверху вниз

const int ledPins[] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11}; // пины линейки
int on_off = HIGH;

void setup() {
  for (int i = 0; i < num_out; ++i) {
    pinMode(ledPins[i], OUTPUT);
  }
}

void circle(int on_off, int tm_delay) {
  for (int j = 0; j < num_out; ++j) {
    int ind = on_off ? j : num_out - 1 - j;
    digitalWrite(ledPins[ind], on_off); // вкл/выкл сегмент
    delay(tm_delay);
  }
}

void loop() {
  circle(on_off, (on_off ? up_time : down_time));
  on_off = !on_off;
}