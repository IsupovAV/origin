#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 10, 9, 8, 7);

const int Y_PIN = A0;
const int X_PIN = A1;
const int SEL_PIN = 3;

const int ledPin = 13;
const int pir1Pin = 2;
int pirState = LOW;
int val = 0;

int last_status = LOW;
int last_x = 512;
bool status = false;

int timeout = 2; // секунды
unsigned long prev_millis = 0;

// изменяет время задержки от 2 до 10 секунд
void change_delay(int x, int &timeout) {
  if (x < 512 - 50 && timeout < 10) {
    timeout++;
  } else if (x > 512 + 50 && timeout > 2) { 
    timeout--;
  }
  delay(200); 
}

int debounce(int last) {
  int current = digitalRead(SEL_PIN);
  if (last != current) {
    delay(5);
    current = digitalRead(SEL_PIN);
  }
  return current;
}

bool is_expired(unsigned long duration) {
  unsigned long current_millis = millis();
  return current_millis - prev_millis >= duration;
}

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(pir1Pin, INPUT);
  Serial.begin(9600);
  pinMode(Y_PIN, INPUT);
  pinMode(X_PIN, INPUT);
  pinMode(SEL_PIN, INPUT_PULLUP);

  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Delay: ");
  lcd.print(timeout);
  lcd.print(" sec");
}

void loop() {
  int curr_status = debounce(last_status);
  if (last_status == HIGH && curr_status == LOW) {
    timeout = 0; 
    lcd.print("Delay: ");
    lcd.print(timeout);
    lcd.print(" sec");
  }
  last_status = curr_status;

  int x = analogRead(X_PIN);

  if (x != last_x) {
    change_delay(x, timeout);
    last_x = x;
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Delay: ");
    lcd.print(timeout);
    lcd.print(" sec");
  }

  val = digitalRead(pir1Pin);
  if (timeout != 0) {
    if (status == false) {
      if (val == HIGH) {
        digitalWrite(ledPin, HIGH);
        Serial.println("Motion detected!");
        prev_millis = millis();  
        status = true;
      }
    } else {
      if (is_expired(timeout * 1000)) {
        digitalWrite(ledPin, LOW);
        Serial.println("Motion ended!");
        Serial.println(timeout);
        status = false;
      }
    }
  }
}
