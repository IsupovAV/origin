#include "rectangle.h"

Rectangle::Rectangle(int a, int b) : Parallelogram(a, b, 90, 90) {
  name = "Прямоугольник";
  std::string msg = check();
  if(!msg.empty()) {
    throw GeometricException(msg);
  }
}

Rectangle::Rectangle(int a, int b, int с, int d, int A, int B, int C, int D)
  : Parallelogram(a, b, с, d, A, B, C, D) {
  name = "Прямоугошльник";
  std::string msg = check();
  if(!msg.empty()) {
    throw GeometricException(msg);
  }
}

std::string Rectangle::get_name()  { return name; }

std::string Rectangle::check()  {
  std::string reason = Parallelogram::check();
  if(get_angle('A') != 90 && get_angle('B') != 90)
    reason = "не все углы 90 градусов ";
  return reason;
}
