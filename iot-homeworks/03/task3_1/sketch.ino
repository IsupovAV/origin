const int SIGNAL = A0;  // пин сигнала потенциометра
const int SURVEY_PERIOD = 100;  // период опроса в миллисекундах

const int SZ = 10;  // размер массива
int arr[SZ];        // массив для фильтра скользящего среднего

// функция фильтрации
int filtering(int x) {
  static int n = 0, y = 0;
  static bool is_full = false;

  y += (x - arr[n]);
  arr[n++] = x;
  n %= SZ;
  if (n == 0) is_full = true;

  return y / (is_full ? SZ : n);
}


void setup() {
  Serial.begin(115200);
  pinMode(A0, INPUT);
}

void loop() {
  int value = analogRead(SIGNAL);
  float angle = map(filtering(value), 0, 1023, -135, 135);
  Serial.print(angle);
  Serial.print(' ');

  delay(SURVEY_PERIOD);
}
