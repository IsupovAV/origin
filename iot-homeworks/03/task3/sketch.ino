#include "Keypad.h"

const int ledPins[] = {12, 11, 10};

const uint8_t ROWS = 4;
const uint8_t COLS = 4;

const char keymap[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

const int intervals[] = {0, 1000, 500, 250};

bool ledStatus[] = {false, false, false};
unsigned long previous_time = 0;
int interval = 0;

byte rowPins[ROWS] = {9, 8, 7, 6};
byte colPins[COLS] = {5, 4, 3, 2};

void keypad_handler(char key);
void show_led();
void blink_led();
void set_status(int n);
bool is_correct_key(char ch);

Keypad key_pad = Keypad(makeKeymap(keymap), rowPins, colPins, ROWS, COLS);

void setup() {
  for (int i = 0; i < 3; i++) {
    pinMode(ledPins[i], OUTPUT);
    digitalWrite(ledPins[i], HIGH); // выключаем все светодиоды при старте
  }
  Serial.begin(115200);
}

void loop() {

  char keypressed = key_pad.getKey();

  if (is_correct_key(keypressed)) {
    keypad_handler(keypressed);
    show_led();
  }

  if(interval > 0){
    unsigned long current_time = millis();
    if (current_time - previous_time >= interval) {
      previous_time = current_time;
      blink_led();
    }
  }
}

void keypad_handler(char key) {
  uint8_t k = key - '0';
  if (k < 8) {
    set_status(k);
  }

  k = key - 'A';
  if (k < 4) {
    interval = intervals[k];
  }
}

void show_led(){
  digitalWrite(ledPins[0], !ledStatus[0]);
  digitalWrite(ledPins[1], !ledStatus[1]);
  digitalWrite(ledPins[2], !ledStatus[2]);

}

void blink_led() {
  for (int i = 0; i < 3; i++) {
    if (ledStatus[i]) {
      digitalWrite(ledPins[i], !digitalRead(ledPins[i]));
    }
  }
}

void set_status(int n) {
  if (n == 0) {
    interval = 0;
  }
  ledStatus[0] = n % 2;
  ledStatus[1] = (n / 2) % 2;
  ledStatus[2] = n / 4;
}

bool is_correct_key(char ch) {
  return (ch != NO_KEY && ch != '8' && ch != '9'
          && ch != '*' && ch != '#');
}
