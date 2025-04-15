const int pinLed[] = {6, 5, 3};  
const int pinButton = 2;

int lastStatus = LOW; //предыдущее состояние кнопки
int counter = 0;          

void setup() {
  for (int i = 0; i < 3; ++i) {
    pinMode(pinLed[i], OUTPUT);
    digitalWrite(pinLed[i], HIGH);
  }
  pinMode(pinButton, INPUT);
  digitalWrite(pinButton, HIGH);
}

void loop() {
	int curStatus = debounce (lastStatus);
	if(lastStatus == HIGH && curStatus == LOW){ //условие нажатия
		segments_on_off(counter, HIGH);
    counter = ++counter % 8;
		segments_on_off(counter, LOW);
	}
	lastStatus = curStatus;
}

void segments_on_off(int n, int on_off){
  if(n % 2){  
    digitalWrite(pinLed[0], on_off);
  }
  if(n / 2 % 2){
    digitalWrite(pinLed[1], on_off);
  }
  if(n / 4){
    digitalWrite(pinLed[2], on_off);
  }
  delay(5);
}

// Функция подавления дребезга 
// last - предыдущее состояние кнопки
int debounce (int last){
  int current = digitalRead(pinButton);
  if (last != current){ //если состояние изменилось
    delay(5);
    current = digitalRead(pinButton);
  }
  return current;
}

