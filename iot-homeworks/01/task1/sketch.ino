const int red = 9;
const int green = 5;
const int blue = 2;

const int time_delay = 1000;

void setup() {
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(blue, OUTPUT);
}

void loop() {
  for(int i = 1; i < 8; ++i){
    on_colors(i);
    clear();
  }
}

void on_colors(int n){
  // n - изменяется от 1 до 7
  // например при n = 3 (011) включится красный и зеленый
  // т.е. будет желтый. Порядок цветов: красный, зеленый,
  // желтый, синий, пурпурный, голубой, белый.
  if(n % 2){  
    digitalWrite(red, HIGH);
  }
  if(n / 2 % 2){
    digitalWrite(green, HIGH);
  }
  if(n / 4){
    digitalWrite(blue, HIGH);
  }
  delay(time_delay);
}

void clear(){
  digitalWrite(red, LOW);
  digitalWrite(green, LOW);
  digitalWrite(blue, LOW);
}
