#include "task3_2.h"

// LedsLine
LedsLine::LedsLine(int *led_pins, int sz, int step)
  : number_leds_(sz), step_(step), curr_led_(0), last_led_(0) {
  for (int i = 0; i < number_leds_; ++i) {
    led_pins_[i] = led_pins[i];
    pinMode(led_pins_[i], OUTPUT);
  }
};

void LedsLine::UpdateLeds() {
  digitalWrite(led_pins_[last_led_], LOW);
  analogWrite(led_pins_[curr_led_], bright_);
};

int LedsLine::GetNumLeds() {
  return number_leds_;
};
int LedsLine::GetCurrLed() {
  return curr_led_;
};
void LedsLine::SetCurrLed(int curr_led) {
  curr_led_ = curr_led;
};
void LedsLine::SetLastLed(int last_led) {
  last_led_ = last_led;
};

int LedsLine::GetBright() {
  return bright_;
};
void LedsLine::SetBright(int bright) {
  bright_ = bright;
};
const int LedsLine::GetStep() const {
  return step_;
};

// Joystick
Joystick::Joystick(const int vert_pin, const int horz_pin, const int sel_pin,
                   const int zero, const int radius)
  : vert_pin_(vert_pin), horz_pin_(horz_pin), sel_pin_(sel_pin), zero_(zero),
    radius_(radius) {
  pinMode(horz_pin_, INPUT);
  pinMode(vert_pin_, INPUT);
  pinMode(sel_pin_, INPUT_PULLUP);
};

void Joystick::ReadJoystick(LedsLine &line) {
  int x_val = analogRead(horz_pin_);
  int y_val = analogRead(vert_pin_);

  int cled = line.GetCurrLed();
  line.SetLastLed(cled);
  if (x_val < zero_ - radius_) {
    line.SetCurrLed(min(cled + 1, line.GetNumLeds() - 1));
  } else if (x_val > zero_ + radius_) {
    line.SetCurrLed(max(cled - 1, 0));
  }

  int bright = line.GetBright();
  int step = line.GetStep();
  if (y_val < zero_ - radius_) {
    line.SetBright(max(bright - step, 0));
  } else if (y_val > zero_ + radius_) {
    line.SetBright(min(bright + step, MAX_BRIGHT));
  }
};

void Joystick::CheckButton(LedsLine &line, const int debounce) {
  if (digitalRead(sel_pin_) == LOW) {
    delay(debounce);
    if (digitalRead(sel_pin_) == LOW) {
      line.SetCurrLed(0);
    }
  }
};
