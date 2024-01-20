#include "isosceles_triangle.h"

IsoscelesTriangle::IsoscelesTriangle(int a, int b, int A, int B) : Triangle(a, b, a, A, B, A) {
  name = "Равнобедренный треугольник";
  std::string msg = check();
  if(!msg.empty()) {
    throw GeometricException(msg);
  }
}

IsoscelesTriangle::IsoscelesTriangle(int a, int b, int c, int A, int B, int C) : Triangle(a, b, c, A, B, C) {
  name = "Равнобедренный треугольник";
  std::string msg = check();
  if(!msg.empty()) {
    throw GeometricException(msg);
  }
}

std::string IsoscelesTriangle::get_name()  { return name; }

std::string IsoscelesTriangle::check() {
  std::string reason = Triangle::check();
  if(get_side('a') != get_side('c')) {
    reason += "сторона a не равна стороне с ";
  }
  if(get_angle('A') != get_angle('C')) {
    reason += "угол A не равен углу C ";
  }

  return reason;
}
