#include "pch.h"

#include "equilateral_triangle.h"

EquilateralTriangle::EquilateralTriangle(int a) : Triangle(a, a, a, 60, 60, 60) {
  name = "Равносторонний треугольник";
}

std::string EquilateralTriangle::get_name() { return name; }
