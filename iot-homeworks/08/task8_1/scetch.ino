#include <IRremote.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>
#include <Wire.h>

// Настройки LCD
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Настройки сервопривода
const int SERVO_PIN = 9;
Servo servo;

// Настройки ИК-приёмника
const int IR_PIN = 2;

// Коды кнопок пульта
const uint16_t digits[10] = {104, 48, 24, 122, 16, 56, 90, 66, 74, 82};
// Команды
const uint16_t BTN_C = 176;    // Кнопка C
const uint16_t BTN_PLAY = 168; // Кнопка PLAY

// Переменные управления
char inputBuffer[4] = ""; // Буфер для ввода (макс. 3 цифры)
int bufferIndex = 0;      // Текущая позиция в буфере
int targetAngle = 0;      // Целевой угол сервопривода

// Сброс ввода, очистка буфера
void resetInput() {
  bufferIndex = 0;
  inputBuffer[0] = '\0';
}

// Инициализация LCD
void initLcd() {
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Ready!");
  lcd.setCursor(0, 1);
  lcd.print("Use 0-9, C, PLAY");
}

// Получение цифры по коду
int getDigit(uint16_t val) {
  for (int i = 0; i < 10; ++i)
    if (digits[i] == val)
      return i;
  return -1;
}

// Обновление дисплея
void updateLcd() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Enter angle:");
  lcd.setCursor(0, 1);
  if (bufferIndex == 0) {
    lcd.print("_"); // Курсор при пустом вводе
  } else {
    lcd.print(inputBuffer);
  }
}

// Печать угла на LCD
void printAngle(int angle) {
  lcd.clear();
  lcd.print("Angle set:");
  lcd.setCursor(0, 1);
  lcd.print(angle);
  lcd.print(" degrees");
  delay(2000);
}

// Печать ошибки при вводе угла
void printErrAngle() {
  lcd.clear();
  lcd.print("Invalid angle!");
  lcd.setCursor(0, 1);
  lcd.print("Use 0-180");
  delay(2000);
}

// Обработчик ввода цифр
void handleDigit(int val) {
  if (bufferIndex < 3) { // Проверка переполнения буфера
    char num = '0' + val; // Конвертация кода в цифру
    inputBuffer[bufferIndex++] = num;
    inputBuffer[bufferIndex] = '\0'; // Завершающий нуль
    updateLcd();
  }
}

// Обработчик нажатия C - сброс ввода
void handleButtC() {
  resetInput();
  lcd.clear();
  lcd.print("Input canceled!");
  delay(1000);
  updateLcd();
}

// Обработчик нажатия PLAY - вывод угла поворта
// и поворот сервопривода на заданный угол.
void handleButtPlay() {
  if (bufferIndex > 0) {
    targetAngle = atoi(inputBuffer); // Конвертация строки в число
    if (targetAngle >= 0 && targetAngle <= 180) {
      servo.write(targetAngle); // поворот сервопривода
      printAngle(targetAngle);  // вывод угла
      resetInput();             // очистка буфера
    } else {
      printErrAngle(); // неправильный угол
      resetInput();
    }
    updateLcd();
  }
}

// Обработка ИК-команд
void handleIRCommand(int code) {
  // Обработка цифр 0-9
  int res = getDigit(code); // если не цифра res = -1
  if (res >= 0 && res < 10) {
    handleDigit(res);
  } else if (code == BTN_C) { // Кнопка C (очистка)
    handleButtC();
  } else if (code == BTN_PLAY) { // Кнопка PLAY (применить угол)
    handleButtPlay();
  }
}

void setup() {
  // Инициализация сервопривода
  servo.attach(SERVO_PIN);
  servo.write(targetAngle); // Стартовая позиция (угол 0 градусов)

  // Инициализация LCD
  initLcd();
  // Инициализация ИК-приёмника
  IrReceiver.begin(IR_PIN);
}

// Основной цикл программы
void loop() {
  if (IrReceiver.decode()) {
    handleIRCommand(IrReceiver.decodedIRData.command); // Обработка ИК-команды
    IrReceiver.resume(); // Готов к новому сигналу
  }
  delay(100); // Задержка для стабильности
}
