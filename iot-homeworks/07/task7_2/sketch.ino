// main.ino
#include "A4988StepperMotor.h"

// Определение пинов для подключения драйвера A4988
#define STEP_PIN 2
#define DIR_PIN 3
#define ENABLE_PIN 4

// Создание объекта для управления шаговым двигателем
// 200 шагов на оборот (1.8 градуса на шаг)
A4988StepperMotor stepper(STEP_PIN, DIR_PIN, ENABLE_PIN, 200);

void setup() {
    Serial.begin(9600);
    Serial.println("Инициализация шагового двигателя...");
    
    // Инициализация двигателя
    stepper.begin();
    
    Serial.println("Готов к работе!");
    delay(2000);
}

void loop() {
    Serial.println("Медленный поворот на 360 градусов по часовой стрелке...");
    
    // Медленная скорость - 30 RPM
    stepper.setSpeed(5);
    
    // Поворот на 360 градусов (200 шагов)
    stepper.step(200);
    
    delay(2000); // Пауза между движениями
    
    Serial.println("Быстрый поворот на 360 градусов против часовой стрелки...");
    
    // Быстрая скорость - 120 RPM
    stepper.setSpeed(30);
    
    // Поворот на 360 градусов в обратную сторону (-200 шагов)
    stepper.step(-200);
    
    delay(3000); // Пауза перед повторением цикла
    
    Serial.println("Цикл завершен. Повторение...");
    Serial.println("---");
}