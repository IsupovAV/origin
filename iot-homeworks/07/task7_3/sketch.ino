#include <Servo.h>

// Пины
const int trigPin = 2;
const int echoPin = 3;
const int servoPin = 9;

// Диапазон расстояний (в см)
const float minDistance = 2.0;
const float maxDistance = 400.0;

Servo servo;

unsigned long lastMeasurementTime = 0;
const unsigned long interval = 10; // 10 мс

// Измерение расстояния с HC-SR04
float measureDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH, 30000); // max 30ms = ~500 см
  float distanceCm = duration * 0.0343 / 2;

  distanceCm = constrain(distanceCm, minDistance, maxDistance);
  return distanceCm;
}

// Преобразование расстояния в угол (обратно пропорционально)
int mapDistanceToAngle(float distance) {
  return map(distance, minDistance, maxDistance, 180, 0);
}

void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  servo.attach(servoPin);
}

void loop() {
  unsigned long currentTime = millis();
  if (currentTime - lastMeasurementTime >= interval) {
    lastMeasurementTime = currentTime;

    float distance = measureDistance();
    int angle = mapDistanceToAngle(distance);

    servo.write(angle);

    Serial.print("Дистанция: ");
    Serial.print(distance);
    Serial.print(" см | Угол: ");
    Serial.println(angle);
  }
}

