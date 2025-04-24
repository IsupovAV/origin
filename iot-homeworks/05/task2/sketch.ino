// Подключаем библиотеку для работы с LCD
#include <LiquidCrystal.h>

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
  for( int i=0; i<3; i++){
    pinMode( rgbPins[i], OUTPUT);
    digitalWrite(rgbPins[i], HIGH);
  }

  lcd.begin(16, 2);
  lcd.clear();
}

void glow_continuously(){
  for( int i=0; i<3; i++)
    digitalWrite( rgbPins[i], LOW);
}

void blink_yellow(){
  digitalWrite(rgbPins[2], HIGH);
  status = !status;
  digitalWrite( rgbPins[0], status);
  digitalWrite( rgbPins[1], status);
  delay(400);
}

void blink_red(){
  digitalWrite(rgbPins[1], HIGH);
  digitalWrite(rgbPins[2], HIGH);
  status = !status;
  digitalWrite( rgbPins[0], status);
}


void loop() {
  cm = readUltrasonicDistance(3, 2) / 58;
  meters = (cm / 100);
  if (meters >= 2.00 && meters <= 4.00)
    glow_continuously();
  else if (meters >= 1.00 && meters < 2.00)
    blink_yellow();
  else
    blink_red();
  lcd.setCursor(0, 0);
  lcd.print("meters:");
  lcd.setCursor(8, 0);
  lcd.print(meters);
  delay(100);
}