const int TIME = 1000;
const int SIZE = 8;     // количество цветов

// no - бесцветный
enum Color {no, red, green, yellow, blue, magenta, aqua, white};

// класс трёхцветный диод
class RgbLed {
  public:
    // конструктор
    RgbLed(int pinR, int pinG, int pinB, bool anode = true) :
      pins_({pinR, pinG, pinB}), anode_(anode) {
      for (int i = 0;  i < 3; ++i) {
        pinMode(pins_[i], OUTPUT);
      }
      AllOff();
    };

    // включить цвет color
    void On(Color color) {
      OnOff(color);
    }

    // выключить цвет color
    void Off(Color color) {
      OnOff(color, false);
    }

    // выключить все цвета
    void AllOff() {
      for (int i = 0; i < 3; ++i)
        digitalWrite(pins_[i], anode_);
    }

  private:
    // функция включения, выключения цвета color в зависимости
    //  от флажка on, чтобы избежать дублирования кода
    void OnOff(Color color, bool on = true) {
      int b = (on && !anode_) || (!on && anode_) ? HIGH : LOW;
      if (color & 1)
        digitalWrite(pins_[0], b);
      if (color & 2)
        digitalWrite(pins_[1], b);
      if (color & 4)
        digitalWrite(pins_[2], b);
    }

    int pins_[3]; // здесь хранятся номера физических контактов
    bool anode_;  // признак анод/катод
};

RgbLed rgb_led(13, 12, 11);
void setup() {
}

void loop() {
  static int c = red; // static сохраняет значение между вызовами
  // цвета идут по кругу в следующем порядке:
  // красный, зелёный, жёлтый, синий, пурпурный, аква, белый, бесцветный
  rgb_led.On(c);
  delay(TIME);
  rgb_led.Off(c);
  c = (c + 1) % SIZE;
}
