const int num_out = 8;

int delay_arr[] = {1000, 500, 250, 100};

int ledPins[] = {
  6, 7, 8, 9, 10, 11, 12, 13
};

void setup() {
  for (int i = 0; i < num_out; ++i) {
    pinMode(ledPins[i], OUTPUT);
  }

}

void loop() {
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < num_out; ++j) {
      digitalWrite(ledPins[j], HIGH);
      delay(delay_arr[i]);
      digitalWrite(ledPins[j], LOW);
    }
  }
}