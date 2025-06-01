// Подключаем библиотеку для работы с LCD
#include <LiquidCrystal.h>

#define DELAY_RED 100
#define DELAY_YELLOW 500

// Инициализируем объект-экран, передаём использованные
LiquidCrystal lcd(12, 11, 10, 4, 8, 7);

float cm;
float meters;
const int rgbPins[] = { 5, 6, 9};
int status = HIGH;

// Функция чтения данных с датчика
long readUltrasonicDistance(int triggerPin, int echoPin) {
  pinMode(triggerPin, OUTPUT); // сброс Trig
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);

  digitalWrite(triggerPin, HIGH); // установка TRIG на 10 мкс
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);

  pinMode(echoPin, INPUT); // измерение длительности ECHO
  int duration = pulseIn(echoPin, HIGH);
  delay(100);
  return duration;
}


void setup() {
  for ( int i = 0; i < 3; i++) {
    pinMode( rgbPins[i], OUTPUT);
    digitalWrite(rgbPins[i], HIGH);
  }
  lcd.begin(16, 2);
  lcd.clear();
}

void shineContinuously() {
  digitalWrite( rgbPins[0], LOW);
  digitalWrite( rgbPins[1], LOW);
  digitalWrite( rgbPins[2], LOW);
}

void blinkYellow() {
  status = !status;
  digitalWrite(rgbPins[2], HIGH);
  digitalWrite( rgbPins[0], status);
  digitalWrite( rgbPins[1], status);
  delay(DELAY_YELLOW);
}

void blinkRed() {
  status = !status;
  digitalWrite(rgbPins[1], HIGH);
  digitalWrite(rgbPins[2], HIGH);
  digitalWrite( rgbPins[0], status);
  delay(DELAY_RED);
}

void display() {
  lcd.setCursor(0, 0);
  lcd.print("meters:");
  lcd.setCursor(8, 0);
  lcd.print(meters);
}

void loop() {
  cm = readUltrasonicDistance(3, 2) / 58;
  meters = (cm / 100);
  display();
  if (meters >= 2.00 && meters <= 4.00) {
    shineContinuously();
  }
  else if (meters >= 1.00 && meters < 2.00) {
    blinkYellow();
  }
  else {
    blinkRed();
  }
}