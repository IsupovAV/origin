const int size_array = 10;
int arr[size_array];

int filtering(int x);

void setup() {
  Serial.begin(115200);
  pinMode(A0, INPUT);

}

void loop() {
  int value = analogRead(A0);
  float angle = map(filtering(value), 0, 1023, -135, 135);
  Serial.print(angle);
  Serial.print(' ');

  delay(100);
}

int filtering(int x) {
  static int n; 
  static int y;
  static bool is_full = false;

  y = y + (x - arr[n]);
  arr[n] = x;
  n = (n + 1) % size_array;
  if(n == 0) is_full = true;
  int d = is_full ? size_array : n;

  return y / d;
}

