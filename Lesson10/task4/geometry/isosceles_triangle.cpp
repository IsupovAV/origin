#include "pch.h"

#include "isosceles_triangle.h"

IsoscelesTriangle::IsoscelesTriangle(int a, int b, int A, int B) : Triangle(a, b, a, A, B, A) {
  name = "Равнобедренный треугольник";
}

std::string IsoscelesTriangle::get_name()  { return name; }

