#include <LiquidCrystal.h>
#include <math.h>

// Инициализируем объект-экран
LiquidCrystal lcd(12, 11, 10, 9, 8, 7);

// датчики OUTы
const int ntc1 = A0;
const int ntc2 = A1;
const int ntc3 = A2;

const int sz_array = 3;
float arr_ntc[sz_array] {0};

void setup() {
  lcd.begin(16, 2);
  lcd.clear();
}

// Функция для перевода показаний датчика в градусы Цельсия
float Getterm(int RawADC) {
  float celsius = 1 / (log(1 / (1023. / RawADC - 1)) / 3950 + 1.0 / 298.15) - 273.15;
  return celsius;
}

// среднее с датчика ntc
float average(int ntc) {
  float data = 0;
  for (int i = 0; i < 10; i++) {
    data += analogRead(ntc);
    delay(100);
  }
  return Getterm(data / 10);
}

// максимальное значение из трёх 
float maximum(float* arr) {
  float mx = arr[0];
  if (arr[1] > mx)
    mx = arr[1];
  if (arr[2] > mx)
    mx = arr[2];
  return mx;
}

// минимальное значение из трёх 
float minimum(float* arr) {
  float mn = arr[0];
  if (arr[1] < mn)
    mn = arr[1];
  if (arr[2] < mn)
    mn = arr[2];
  return mn;
}

// среднее из трёх
float avgValue(float* arr) {
  float sum = arr[0] + arr[1] + arr[2];
  return sum / sz_array;
}

void loop() {
  arr_ntc[0] = average(ntc1);
  arr_ntc[1] = average(ntc2);
  arr_ntc[2] = average(ntc3);

  // вывод
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("MX=");
  lcd.print(maximum(arr_ntc), 1);

  lcd.setCursor(8, 0);
  lcd.print("MN=");
  lcd.print(minimum(arr_ntc), 1);

  lcd.setCursor(0, 1);
  lcd.print("AVG=");
  lcd.print(avgValue(arr_ntc));

  delay(500);
}
