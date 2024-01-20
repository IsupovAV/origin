#include "square.h"

Square::Square(const int a) : Rectangle(a, a) {
  name = "Квадрат";
  std::string msg = check();
  if(!msg.empty()) {
    throw GeometricException(msg);
  }
}

Square::Square(int a, int b, int c, int d, int A, int B, int C, int D)
  : Rectangle(a, b, c, d, A, B, C, D) {
  name = "Квадрат";
  std::string msg = check();
  if(!msg.empty()) {
    throw GeometricException(msg);
  }
}

std::string Square::get_name()  { return name; }

std::string Square::check()  {
  std::string reason = Rectangle::check();
  if(!reason.empty())
    return reason;
  if(get_side('a') != get_side('b'))
    reason = "все стороны не равны";
  return reason;
}


