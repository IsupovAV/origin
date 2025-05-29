#include <LiquidCrystal.h>
// Подключаем стандартную библиотеку LiquidCrystal
// Инициализируем объект-экран, передаём использованные
// для подключения контакты на Arduino в порядке: 
// RS, E, D4, D5, D6, D7
LiquidCrystal lcd(12, 11, 10, 9, 8, 7);

const int VERT_PIN = A1;
const int HORZ_PIN = A2;
const int SEL_PIN = 2;

const int MAX_POSITION = 15;
const int ZERO = 512;       // "ноль" джойстика
const int RADIUS = 50;      // погрешность
const int DEBOUNCE = 10;    // задержка при чтении кнопки
const int PERIOD = 100;     // период опроса

int position = 0;           // позиция курсора на экране
bool line_changed = false;  // флаг изменения текущей линии
char symbol = 'A' - 1;      // текущий символ
int last_status = LOW;      // предыдущее состояние кнопки
int curr_status = LOW;      // текущее состояние кнопки
int last_x = ZERO;          // предыдущее значение по оси X
int last_y = ZERO;          // предыдущее значение по оси Y

void setup(){
  pinMode(HORZ_PIN, INPUT);
  pinMode(VERT_PIN, INPUT);
  pinMode(SEL_PIN, INPUT_PULLUP);

  // устанавливаем размер (количество столбцов и строк) экрана
  lcd.begin(16, 2);
  // ощищаем экран
  lcd.clear();
  // Включаем курсор
  lcd.cursor();
  // Устанавливаем начальную позицию и символ "_"
  lcd.setCursor(position, line_changed);
}

void loop() {
  curr_status = debounce(last_status);
  if (last_status == HIGH && curr_status == LOW) {  // условие нажатия
    line_changed = !line_changed; // переключаем строку при нажатии кнопки
    lcd.setCursor(position, line_changed);
    symbol = 'A' - 1;
  }
  last_status = curr_status;

  read_joystick();
}

void read_joystick() {
  int x_val = analogRead(HORZ_PIN);
  int y_val = analogRead(VERT_PIN);

  if (x_val != last_x) { 
    delay(PERIOD);
    horizontal_move(x_val, position);
    lcd.setCursor(position, line_changed);
  }
  if (y_val != last_y) { 
    vertical_move(y_val, symbol);
    delay(PERIOD);

    lcd.print(symbol);
    lcd.setCursor(position, line_changed);//возврат курсора
  }
}

void horizontal_move(int x, int &position) {
  if (x < ZERO - RADIUS) { // Движение вправо
    position = position < MAX_POSITION ? position + 1: 0;
  }
  else if (x > ZERO + RADIUS) { // Движение влево
    position = position > 0 ? position - 1: MAX_POSITION;
  }
  delay(PERIOD);
}

void vertical_move(int y, char &symbol) {
  if (y > ZERO + RADIUS) {
    symbol = symbol < 'Z' ? symbol + 1: 'A';
  } else if (y < ZERO - RADIUS) {
    symbol = symbol > 'A' ? symbol - 1: 'Z';
  }
  
  delay(PERIOD);
}

/* Функция подавления дребезга (last - предыдущее состояние кнопки) */
int debounce(int last) {
  int current = digitalRead(SEL_PIN);
  if (last != current) {  // если состояние изменилось
    delay(DEBOUNCE);
    current = digitalRead(SEL_PIN);
  }
  return current;
}

