const int num_out = 8;
const int delay_up = 500;
const int delay_down = 1000;

int ledPins[] = {
  6, 7, 8, 9, 10, 11, 12, 13
};   

void setup() {
  for(int i = 0; i < num_out; ++i){
    pinMode(ledPins[i], OUTPUT);
  }

}

void loop() {
  for(int i = 0; i < num_out; ++i){
    digitalWrite(ledPins[i], HIGH);
    delay(delay_up);
  }

  for(int i = num_out - 1; i >= 0; --i){
    digitalWrite(ledPins[i], LOW);
    delay(delay_down);
  }
}
