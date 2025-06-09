// A4988StepperMotor.h
#ifndef A4988STEPPERMOTOR_H
#define A4988STEPPERMOTOR_H

#include <Arduino.h>

class A4988StepperMotor {
private:
    int stepPin;
    int dirPin;
    int enablePin;
    int stepsPerRevolution;
    int currentDelay;
    
public:
    // Конструктор
    A4988StepperMotor(int stepPin, int dirPin, int enablePin, int stepsPerRevolution = 200);
    
    // Инициализация
    void begin();
    
    // Задание скорости вращения (RPM)
    void setSpeed(float rpm);
    
    // Перемещение на заданное число шагов
    void step(int steps);
    
    // Включение/выключение двигателя
    void enable();
    void disable();
};

#endif