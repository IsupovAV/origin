// Решение получено с помощью нейросети:
// https://claude.ai бесплатная версия claude sonet4, код и json.
// Управление шаговым двигателем с Arduino UNO
// Подключения:
// Шаговый двигатель: пины 8, 9, 10, 11
// Кнопка "Старт/Стоп": пин 2
// Кнопка "Влево": пин 3
// Кнопка "Вправо": пин 4
// Потенциометр: пин A0

#include <Stepper.h>

// Константы
const int STEPS_PER_REV = 200;  // Количество шагов на оборот
const int MIN_SPEED = 0;        // Минимальная скорость (rpm)
const int MAX_SPEED = 100;      // Максимальная скорость (rpm)
const int DEBOUNCE_DELAY = 50;  // Задержка для подавления дребезга (мс)

// Пины подключения
const int STEPPER_PIN1 = 8;
const int STEPPER_PIN2 = 9;
const int STEPPER_PIN3 = 10;
const int STEPPER_PIN4 = 11;
const int START_STOP_PIN = 2;
const int LEFT_PIN = 3;
const int RIGHT_PIN = 4;
const int POTENTIOMETER_PIN = A0;

// Создание объекта шагового двигателя
Stepper stepper(STEPS_PER_REV, STEPPER_PIN1, STEPPER_PIN2, STEPPER_PIN3, STEPPER_PIN4);

// Переменные состояния
bool motorRunning = false;      // Состояние работы двигателя
int direction = 1;              // Направление вращения (1 - вправо, -1 - влево)
int currentSpeed = 50;          // Текущая скорость в rpm
unsigned long lastStepTime = 0; // Время последнего шага
unsigned long stepDelay = 0;    // Задержка между шагами

// Переменные для подавления дребезга
bool lastStartStopState = HIGH;
bool lastLeftState = HIGH;
bool lastRightState = HIGH;
unsigned long lastStartStopTime = 0;
unsigned long lastLeftTime = 0;
unsigned long lastRightTime = 0;
bool startStopPressed = false;
bool leftPressed = false;
bool rightPressed = false;

void setup() {
  // Инициализация Serial порта
  Serial.begin(9600);
  Serial.println("=== Управление шаговым двигателем ===");
  Serial.println("Готов к работе!");

  // Настройка пинов кнопок как входы с подтяжкой
  pinMode(START_STOP_PIN, INPUT_PULLUP);
  pinMode(LEFT_PIN, INPUT_PULLUP);
  pinMode(RIGHT_PIN, INPUT_PULLUP);

  // Установка начальной скорости
  stepper.setSpeed(currentSpeed);
  calculateStepDelay();

  // Вывод начального состояния
  printStatus();
}

void loop() {
  // Обработка кнопок
  handleButtons();

  // Обновление скорости по потенциометру
  updateSpeed();

  // Управление двигателем
  controlMotor();

  delay(10); // Небольшая задержка для стабильности
}

// Функция обработки всех кнопок
void handleButtons() {
  handleStartStopButton();
  handleDirectionButtons();
}

// Функция обработки кнопки "Старт/Стоп"
void handleStartStopButton() {
  bool reading = digitalRead(START_STOP_PIN);

  if (reading != lastStartStopState) {
    lastStartStopTime = millis();
  }

  if ((millis() - lastStartStopTime) > DEBOUNCE_DELAY) {
    if (reading != startStopPressed) {
      startStopPressed = reading;
      if (startStopPressed == LOW) { // Кнопка нажата
        motorRunning = !motorRunning;
        Serial.print("Кнопка 'Старт/Стоп' нажата - ");
        Serial.println(motorRunning ? "СТАРТ" : "СТОП");
        printStatus();
      }
    }
  }

  lastStartStopState = reading;
}

// Функция обработки кнопок направления
void handleDirectionButtons() {
  // Обработка кнопки "Влево"
  bool leftReading = digitalRead(LEFT_PIN);

  if (leftReading != lastLeftState) {
    lastLeftTime = millis();
  }

  if ((millis() - lastLeftTime) > DEBOUNCE_DELAY) {
    if (leftReading != leftPressed) {
      leftPressed = leftReading;
      if (leftPressed == LOW) { // Кнопка нажата
        direction = -1;
        Serial.println("Кнопка 'Влево' нажата - направление: ВЛЕВО");
        printStatus();
      }
    }
  }

  lastLeftState = leftReading;

  // Обработка кнопки "Вправо"
  bool rightReading = digitalRead(RIGHT_PIN);

  if (rightReading != lastRightState) {
    lastRightTime = millis();
  }

  if ((millis() - lastRightTime) > DEBOUNCE_DELAY) {
    if (rightReading != rightPressed) {
      rightPressed = rightReading;
      if (rightPressed == LOW) { // Кнопка нажата
        direction = 1;
        Serial.println("Кнопка 'Вправо' нажата - направление: ВПРАВО");
        printStatus();
      }
    }
  }

  lastRightState = rightReading;
}

// Функция обновления скорости по потенциометру
void updateSpeed() {
  int potValue = analogRead(POTENTIOMETER_PIN);
  int newSpeed = map(potValue, 0, 1023, MIN_SPEED, MAX_SPEED);

  // Обновляем скорость только если она изменилась значительно
  if (abs(newSpeed - currentSpeed) > 2) {
    currentSpeed = newSpeed;
    stepper.setSpeed(currentSpeed);
    calculateStepDelay();
    Serial.print("Скорость изменена: ");
    Serial.print(currentSpeed);
    Serial.println(" rpm");
  }
}

// Функция расчета задержки между шагами
void calculateStepDelay() {
  // Расчет задержки в микросекундах между шагами
  // rpm = шагов в минуту, нужно перевести в микросекунды между шагами
  stepDelay = (60L * 1000L * 1000L) / (currentSpeed * STEPS_PER_REV);
}

// Функция управления двигателем
void controlMotor() {
  if (motorRunning) {
    unsigned long currentTime = micros();
    if (currentTime - lastStepTime >= stepDelay) {
      // Делаем один шаг в заданном направлении
      stepper.step(direction);
      lastStepTime = currentTime;
    }
  }
}

// Функция вывода текущего состояния
void printStatus() {
  Serial.println("--- Текущее состояние ---");
  Serial.print("Двигатель: ");
  Serial.println(motorRunning ? "РАБОТАЕТ" : "ОСТАНОВЛЕН");
  Serial.print("Направление: ");
  Serial.println(direction == 1 ? "ВПРАВО" : "ВЛЕВО");
  Serial.print("Скорость: ");
  Serial.print(currentSpeed);
  Serial.println(" rpm");
  Serial.println("------------------------");
}