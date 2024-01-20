#include "right_triangle.h"

RightTriangle::RightTriangle(int a, int b, int c, int A, int B)
  : Triangle(a, b, c, A, B, 90) {
  name = "Прямоугольный треугольник";
  std::string msg = check();
  if(!msg.empty()) {
    throw GeometricException(msg);
  }
}

RightTriangle::RightTriangle(int a, int b, int c, int A, int B, int C)
  : Triangle(a, b, c, A, B, C) {
  name = "Прямоугольный треугольник";
  std::string msg = check();
  if(!msg.empty()) {
    throw GeometricException(msg);
  }
}

std::string RightTriangle::get_name() { return name; }

std::string RightTriangle::check() {
  std::string reason = Triangle::check();
  if(get_angle('C') != 90) {
    reason += "угол C не равен 90 градусов ";
  }

  return reason;
}
