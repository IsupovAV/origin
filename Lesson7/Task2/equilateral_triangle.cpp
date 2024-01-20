#include "equilateral_triangle.h"

EquilateralTriangle::EquilateralTriangle(int a) : Triangle(a, a, a, 60, 60, 60) {
  name = "Равносторонний треугольник";
  std::string msg = check();
  if(!msg.empty()) {
    throw GeometricException(msg);
  }
}

EquilateralTriangle::EquilateralTriangle(int a, int b, int c, int A, int B, int C)
  : Triangle(a, b, c, A, B, C) {
  name = "Равносторонний треугольник";
  std::string msg = check();
  if(!msg.empty()) {
    throw GeometricException(msg);
  }
}

std::string EquilateralTriangle::get_name() { return name; }

std::string EquilateralTriangle::check() {
  std::string reason = Triangle::check();
  if(get_side('a') != get_side('b') || get_side('a') != get_side('c') || get_side('b')  != get_side('c'))
    reason += "стороны не равны ";
  if(get_angle('A') != 60 || get_angle('B') != 60 || get_angle('C') != 60)
    reason += "не все углы равны 60 градусам ";

  return  reason;
}
