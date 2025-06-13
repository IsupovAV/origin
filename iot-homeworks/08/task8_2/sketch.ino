#include <Stepper.h>

const int stepsPerRevolution = 200; // шагов на оборот
const int pinStartStop = 3;         // старт/стоп пин
const int pinDirection = 2; // пин направления вращения
const int speed = 50; // скорость мотора

volatile bool motorRunning = false; // признак запуска
volatile int direction = 1;         // направление вращения

Stepper stepper(stepsPerRevolution, 10, 11, 9, 8); // порядок важен!

////////// Обработчики прерываний //////////
// Запуск/Останов мотора
void toggleMotor() {
  motorRunning = !motorRunning;
}

// Изменить направление вращения:
// "1" по часовой стрелке, "-1" против часовой стрелки)
void changeDirection() {
  direction = -direction;
}

// Функция инициализации
void setup() {
  stepper.setSpeed(speed); // скорость мотора, об/мин

  pinMode(pinStartStop, INPUT_PULLUP);
  pinMode(pinDirection, INPUT_PULLUP);

  // подключение обработчиков
  attachInterrupt(digitalPinToInterrupt(pinStartStop), toggleMotor, FALLING);
  attachInterrupt(digitalPinToInterrupt(pinDirection), changeDirection,
                  FALLING);
}

// Основной цикл
void loop() {
  if (motorRunning) {
    stepper.step(direction * (stepsPerRevolution / speed));
  }
}
