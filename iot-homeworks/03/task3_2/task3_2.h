#include <Arduino.h>

const int SZ = 6;           // максимум светодиодов в линейке
const int MAX_BRIGHT = 250; // максимальная яркость светодиода
const int DEBOUNCE = 10;    // задержка при чтении кнопки
const int PERIOD = 100;     // период опроса

/// @brief класс динейка светодиодов
class LedsLine {
  public:
    LedsLine(int *led_pins, int sz, int step);

    void UpdateLeds(); // обновить свечение текущего светодиода

    int GetNumLeds();              // вернуть количество светодиодов в линейке
    int GetCurrLed();              // вернуть номер текущего светодиода
    void SetCurrLed(int curr_led); // установить номер текущего светодиода
    void SetLastLed(int last_led); // установить номер предыдущего светодиода
    int GetBright();               // вернуть текщую яркость
    void SetBright(int bright);    // установить текщую яркость
    const int GetStep() const;     // вернуть шаг увеличения яркости

  private:
    int led_pins_[SZ];      // массив для хранения пинов
    const int number_leds_; // число реальных светодиодов
    const int step_;        // шаг увелиения яркости
    int curr_led_;          // индекс текущего светодиода
    int last_led_;          // индекс предыдущего светодиода
    int bright_;            // яркость текущего светодиода
};

/// @brief класс Joystick для управления линейкой светодиодов
class Joystick {
  public:
    Joystick(const int vert_pin, const int horz_pin, const int sel_pin,
             const int zero, const int radius);
    void ReadJoystick(
      LedsLine &line); // читать и обработать данные джойстика по осям X,Y
    void CheckButton(LedsLine &line,
                     const int debounce); // обработать нажатие кнопки

  private:
    const int vert_pin_; // VERT - выход вертикальной оси (аналоговый)
    const int horz_pin_; // HORZ - выход горизонтальной оси (аналоговый)
    const int sel_pin_;  // SEL - кнопка нажатия
    const int zero_;     // ноль джойстика
    const int radius_;   // пороговое значение
};
