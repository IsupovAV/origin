#include <LiquidCrystal.h>
#include <math.h>

#define DELAY_READ 10   // Задержка чтения
#define NUM_READ 10     // Количество чтений для усреднения

// Инициализируем объект-экран
LiquidCrystal lcd(12, 11, 10, 9, 8, 7);

// датчики OUTы
const int ntc1 = A0;
const int ntc2 = A1;
const int ntc3 = A2;

const int sz_array = 3;
float arr_ntc[sz_array] = {0, 0, 0};

void setup() {
  lcd.begin(16, 2);
  lcd.clear();
  arr_ntc[0] = average(ntc1);
  arr_ntc[1] = average(ntc2);
  arr_ntc[2] = average(ntc3);
}

// Функция для перевода показаний датчика в градусы Цельсия
float Celsius(int RawADC) {
  float celsius = 1 / (log(1 / (1023. / RawADC - 1)) / 3950. + 1.0 / 298.15) - 273.15;
  return celsius;
}

// среднее с датчика ntc
float average(int ntc) {
  float data = 0;
  for (int i = 0; i < NUM_READ; i++) {
    data += analogRead(ntc);
    delay(DELAY_READ);
  }
  return Celsius(data / NUM_READ);
}

// максимальное значение из трёх
float maximum(float* arr) {
  return max(max(arr[0], arr[1]), arr[2]);;
}

// минимальное значение из трёх
float minimum(float* arr) {
  return min(min(arr[0], arr[1]), arr[2]);
}

// среднее из трёх
float avgValue(float* arr) {
  return (arr[0] + arr[1] + arr[2])/ sz_array;
}

// вывод
void displayData() {
  lcd.setCursor(0, 0);
  lcd.print("MX=");
  lcd.print(maximum(arr_ntc), 1);

  lcd.setCursor(8, 0);
  lcd.print("MN=");
  lcd.print(minimum(arr_ntc), 1);

  lcd.setCursor(0, 1);
  lcd.print("AVG=");
  lcd.print(avgValue(arr_ntc));
}

void loop() {
  arr_ntc[0] = average(ntc1);
  arr_ntc[1] = average(ntc2);
  arr_ntc[2] = average(ntc3);
  displayData();
}
