#pragma once

#include "triangle.h"

// Равносторонний треугольник
class EquilateralTriangle : public Triangle {
public:
  explicit EquilateralTriangle(int a);

  // полный контруктор для проверки работы с исключениями
  explicit EquilateralTriangle(int a, int b, int c, int A, int B, int C);

  std::string get_name() override;

  std::string check() override;
};
