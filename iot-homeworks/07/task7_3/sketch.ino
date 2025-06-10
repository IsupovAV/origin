#include <Servo.h>

// Пины
const int echoPin = 2;
const int trigPin = 3;
const int servoPin = 9;

// Диапазон расстояний (в см)
const int minDistance = 0;
const int maxDistance = 400;

Servo servo;

const unsigned int interval = 10; // 10 мс

// Параметры для усреднения
const int numReadings = 10;   // Количество измерений для усреднения
float readings[numReadings];  // Массив для хранения измерений
int readIndex = 0;            // Текущий индекс чтения
float total = 0;              // Сумма измерений
float averageDistance = 0;    // Усредненное расстояние

// Вывод в консоль
void printState(int angle){
  Serial.print("Дистанция: ");
  Serial.print(averageDistance, 0);
  Serial.print(" см | Угол: ");
  Serial.println(angle);
}

// Измерение расстояния с HC-SR04
long measureDistance() {
  // Генерируем ультразвуковой импульс
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Измеряем длительность ответного импульса
  long duration = pulseIn(echoPin, HIGH, 30000); // Таймаут 30 мс (~5м)

  // Рассчитываем расстояние
  if (duration == 0) {
    // Если превышен таймаут, возвращаем -1
    return -1;
  }
  return duration / 58;
}

// Преобразование расстояния в угол (обратно пропорционально)
int mapDistanceToAngle(float distance) {
  float res = map(distance, minDistance, maxDistance, 180, 0);
  return constrain(res, 0, 180); 
}

// метод скользящего среднего
void rollingAverage(float data){
  // Обновляем сумму: убираем старое значение, добавляем новое
  total = total - readings[readIndex];
  readings[readIndex] = data;
  total = total + readings[readIndex];
    
  // Переходим к следующей позиции в массиве
  readIndex = (readIndex + 1) % numReadings;
    
  // Рассчитываем среднее значение
  averageDistance = total / numReadings;
}

void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Инициализация массива нулевыми значениями
  for (int i = 0; i < numReadings; i++) {
    readings[i] = 0;
  }  
  servo.attach(servoPin);
}

void loop() {
  // Выполняем новое измерение
  float distance = measureDistance();
  
  if (distance >= 0) { // Игнорируем ошибочные измерения
    rollingAverage(distance);

    // Переводим в градусы
    int angle = mapDistanceToAngle(averageDistance);
    servo.write(angle);
    printState(angle);  // Печать состояния
  }

  delay(interval); // Интервал между измерениями
}  

