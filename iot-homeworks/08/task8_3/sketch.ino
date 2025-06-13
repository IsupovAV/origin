#include <Arduino.h>

#include <TimerOne.h>

const int BUTTON_PIN = 2; // Пин кнопки (прерывание 0)
const int LED_PIN = 13; // Пин светодиода (можно использовать встроенный)

// Временные константы (в миллисекундах)
const int DOT_DURATION = 200;   // Длительность точки
const int DASH_DURATION = 600;  // Длительность тире
const int PAUSE_DURATION = 300; // Пауза между символами
const int LETTER_PAUSE = 400;   // Пауза между буквами

// Переменные для обработки SOS сигнала
volatile bool startSOS = false; // Флаг запуска SOS
volatile bool ledState = false; // Состояние светодиода
volatile int sosStep = 0; // Текущий шаг в последовательности SOS
volatile unsigned long timerCounter = 0; // Счетчик таймера
volatile unsigned long targetTime = 0; // Целевое время для текущего шага

// SOS последовательность: S(...) O(---) S(...)
// Массив длительностей для каждого шага
const int sosPattern[] = {
    // S: . . .
    DOT_DURATION, PAUSE_DURATION, DOT_DURATION, PAUSE_DURATION, DOT_DURATION,
    LETTER_PAUSE,
    // O: - - -
    DASH_DURATION, PAUSE_DURATION, DASH_DURATION, PAUSE_DURATION, DASH_DURATION,
    LETTER_PAUSE,
    // S: . . .
    DOT_DURATION, PAUSE_DURATION, DOT_DURATION, PAUSE_DURATION, DOT_DURATION,
    0};

// Состояния светодиода для каждого шага (включить/выключить)
const bool sosLedStates[] = {
    // S: ON OFF ON OFF ON OFF
    true, false, true, false, true, false,
    // O: ON OFF ON OFF ON OFF
    true, false, true, false, true, false,
    // S: ON OFF ON OFF ON OFF
    true, false, true, false, true, false};

// Обработчик прерывания от кнопки
void buttonISR() {
  static unsigned long lastInterrupt = 0;
  unsigned long currentTime = millis();

  // Защита от дребезга контактов (debounce) - игнорируем нажатия чаще 200мс
  if (currentTime - lastInterrupt > 200) {
    if (!startSOS) { // Запускаем SOS только если он не активен
      startSOS = true;
      sosStep = 0;
      timerCounter = 0;
      targetTime = sosPattern[0]; // Устанавливаем время для первого шага
      ledState =
          sosLedStates[0]; // Устанавливаем состояние LED для первого шага
      digitalWrite(LED_PIN, ledState ? HIGH : LOW);

      Serial.println("=== Запуск SOS сигнала! ===");
      // Serial.print("Шаг 0: ");
      // Serial.print(ledState ? "LED ON" : "LED OFF");
      // Serial.print(" на ");
      // Serial.print(targetTime);
      // Serial.println(" мс");
    } else {
      Serial.println("SOS уже активен, ожидайте завершения...");
    }
    lastInterrupt = currentTime;
  }
}

// Обработчик прерывания от таймера (вызывается каждую 1 мс)
void timerISR() {
  if (startSOS) {
    timerCounter++;

    // Проверяем, достигли ли мы целевого времени для текущего шага
    if (timerCounter >= targetTime) {
      sosStep++; // Переходим к следующему шагу

      // Проверяем, закончилась ли вся последовательность SOS
      if (sosStep >= 18 || sosPattern[sosStep] == 0) {
        // Завершаем последовательность SOS
        startSOS = false;
        digitalWrite(LED_PIN, LOW); // Выключаем светодиод
        sosStep = 0;
        timerCounter = 0;
        Serial.println("=== SOS сигнал завершен ===");
        Serial.println("Готов к новому запуску.\n");
      } else {
        // Настраиваем следующий шаг
        timerCounter = 0; // Сбрасываем счетчик
        targetTime = sosPattern[sosStep]; // Устанавливаем новое целевое время
        ledState = sosLedStates[sosStep]; // Устанавливаем новое состояние LED
        digitalWrite(LED_PIN, ledState ? HIGH : LOW);

        // Отладочный вывод
        // Serial.print("Шаг ");
        // Serial.print(sosStep);
        // Serial.print(": ");
        // Serial.print(ledState ? "LED ON" : "LED OFF");
        // Serial.print(" на ");
        // Serial.print(targetTime);
        // Serial.println(" мс");
      }
    }
  }
}

void setup() {
  // Инициализация пинов
  pinMode(BUTTON_PIN, INPUT_PULLUP); // Кнопка с подтяжкой
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  // Настройка внешнего прерывания для кнопки
  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), buttonISR, FALLING);

  // Инициализация TimerOne
  // Устанавливаем период 1000 микросекунд = 1 миллисекунда
  Timer1.initialize(1000);
  Timer1.attachInterrupt(timerISR); // Привязываем функцию обработки прерывания

  // Инициализация Serial для отладки
  Serial.begin(9600);
  Serial.println("SOS Generator готов. Нажмите кнопку для запуска SOS.");
  Serial.println("Паттерн SOS: ...---... (точка=200мс, тире=600мс)");
}

void loop() {
  // Основной цикл пуст - вся логика выполняется в прерываниях
  delay(100);
}
