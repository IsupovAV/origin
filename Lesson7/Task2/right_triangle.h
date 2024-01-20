#pragma once

#include "triangle.h"

// Прямоугольный треугольник
class RightTriangle : public Triangle {
public:
  RightTriangle(int a, int b, int c, int A, int B);

  // Полный конструктор для проверки работы исключений
  RightTriangle(int a, int b, int c, int A, int B, int C);

  std::string get_name() override;

  std::string check() override;

};
