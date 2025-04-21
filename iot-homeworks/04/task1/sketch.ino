#define SEG_COUNT 8
#define BUTTON 11

const int firstSeg = 2;

const byte numberSegments[16] = {
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

void setup() {
  for (int i = 0; i < SEG_COUNT; ++i) {
    pinMode(i + firstSeg, OUTPUT);
    digitalWrite(i + firstSeg, HIGH);
  }

  pinMode(BUTTON, INPUT);
  digitalWrite(BUTTON, HIGH);
}

void loop() {
  static int number = 0;
  int curr = debounce(last);
  if(last == HIGH && curr == LOW){
    int mask;
    bool enableSegment;
    // число для отображения - количество секунд
    number = number % 16;
    mask = numberSegments[number];
    for (int i = 0; i < SEG_COUNT; ++i) {
      enableSegment = bitRead(mask, i);
      digitalWrite(i + firstSeg, enableSegment);
    }
    ++number;
  }
  last = curr;
}

int debounce(int last){
  int curr = digitalRead(BUTTON);
  if(last != curr){
    delay(5);
    curr = digitalRead(BUTTON);
  }

  return curr;
}
