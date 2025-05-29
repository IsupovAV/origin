#define SEGS_COUNT 8  // количество сегментов
#define NDIGITS 16    // количество цифр
#define BUTTON 11     // пин кнопки
#define FIRST_SEG 2   // пин sevseg1:A

const int bounceTime = 5; // время "дребезга"

const byte numbers[NDIGITS] = {
  0b11000000, //0
  0b11111001, //1
  0b10100100, //2
  0b10110000, //3
  0b10011001, //4
  0b10010010, //5
  0b10000010, //6
  0b11111000, //7
  0b10000000, //8
  0b10010000, //9
  0b10001000, //A - 10
  0b10000011, //b - 11
  0b11000110, //C - 12
  0b10100001, //d - 13
  0b10000110, //E - 14
  0b10001110, //F - 15
};

int last = LOW;   // состояния кнопки

int debounce(int last) {
  int curr = digitalRead(BUTTON);
  if (last != curr) {
    delay(bounceTime);
    curr = digitalRead(BUTTON);
  }
  return curr;
}

void setup() {
  for (int i = 0; i < SEGS_COUNT; ++i) {
    pinMode(i + FIRST_SEG, OUTPUT);
    digitalWrite(i + FIRST_SEG, HIGH);
  }
  pinMode(BUTTON, INPUT);
  digitalWrite(BUTTON, HIGH);
}

void loop() {
  static int number = 0;
  int curr = debounce(last);
  if (last == HIGH && curr == LOW) {
    number = number % NDIGITS;
    for (int i = 0; i < SEGS_COUNT; ++i) {
      bool enableSegment = bitRead(numbers[number], i);
      digitalWrite(i + FIRST_SEG, enableSegment);
    }
    ++number;
  }
  last = curr;
}

