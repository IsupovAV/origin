const int VERT_PIN = A1;
const int HORZ_PIN = A2;
const int SEL_PIN = 2;

const int ZERO = 512;       // "ноль" джойстика
const int RADIUS = 50;      // погрешность
const int DEBOUNCE = 10;    // задержка при чтении кнопки
const int PERIOD = 100;     // период опроса
const int NUMBER_LEDS = 6;  // число светодиодов
const int STEP = 10;        // шаг изменения яркости

const int led_pins[] = {11, 10, 9, 6, 5, 3};

int curr_led = 0;     // индекс текущего светодиода
int last_led = 0;
int bright = 10;      // яркость текущего свтодиода

void readJoystick();  // чтения положения джойстика
void checkButton();   // проверка нажатия кнопки джойстика
void updateLeds();    // обновить состояния светодиодов

void setup() {
  for (int i = 0; i < NUMBER_LEDS; i++) {
    pinMode(led_pins[i], OUTPUT);
  }

  pinMode(HORZ_PIN, INPUT);
  pinMode(VERT_PIN, INPUT);
  pinMode(SEL_PIN, INPUT_PULLUP);
}

void loop() {
  readJoystick();
  checkButton();
  updateLeds();
  delay(PERIOD);
}

void readJoystick() {
  int x_val = analogRead(HORZ_PIN);
  int y_val = analogRead(VERT_PIN);

  last_led = curr_led;
  if (x_val < ZERO - RADIUS) {
    curr_led = min(curr_led + 1, NUMBER_LEDS - 1);
  } else if (x_val > ZERO + RADIUS) {
    curr_led = max(curr_led - 1, 0);
  }

  if (y_val < ZERO - RADIUS) {
    bright = max(bright - STEP, 0);
  } else if (y_val > ZERO + RADIUS) {
    bright = min(bright + STEP, 250);
  }
}

void checkButton() {
  if (digitalRead(SEL_PIN) == LOW) {
    delay(DEBOUNCE);
    if (digitalRead(SEL_PIN) == LOW) {
      curr_led = 0;
    }
  }
}

void updateLeds() {
  digitalWrite(led_pins[last_led], LOW);
  analogWrite(led_pins[curr_led], bright);
}
