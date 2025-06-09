// A4988StepperMotor.cpp
#include "A4988StepperMotor.h"

A4988StepperMotor::A4988StepperMotor(int stepPin, int dirPin, int enablePin, int stepsPerRevolution) {
    this->stepPin = stepPin;
    this->dirPin = dirPin;
    this->enablePin = enablePin;
    this->stepsPerRevolution = stepsPerRevolution;
    this->currentDelay = 1000; // По умолчанию медленная скорость
}

void A4988StepperMotor::begin() {
    pinMode(stepPin, OUTPUT);
    pinMode(dirPin, OUTPUT);
    pinMode(enablePin, OUTPUT);
    enable();
}

void A4988StepperMotor::setSpeed(float rpm) {
    // Расчет задержки между шагами для заданной скорости в RPM
    // Задержка в микросекундах = 60,000,000 / (RPM * stepsPerRevolution * 2)
    // Деление на 2 учитывает HIGH и LOW состояния импульса
    long delayMicroseconds = 60000000L / (rpm * stepsPerRevolution * 2);
    currentDelay = delayMicroseconds;
}

void A4988StepperMotor::step(int steps) {
    // Определение направления
    if (steps > 0) {
        digitalWrite(dirPin, HIGH); // По часовой стрелке
    } else {
        digitalWrite(dirPin, LOW);  // Против часовой стрелки
        steps = -steps; // Делаем количество шагов положительным
    }
    
    // Выполнение шагов
    for (int i = 0; i < steps; i++) {
        digitalWrite(stepPin, HIGH);
        delayMicroseconds(currentDelay);
        digitalWrite(stepPin, LOW);
        delayMicroseconds(currentDelay);
    }
}

void A4988StepperMotor::enable() {
    digitalWrite(enablePin, LOW); // LOW включает драйвер
}

void A4988StepperMotor::disable() {
    digitalWrite(enablePin, HIGH); // HIGH выключает драйвер
}