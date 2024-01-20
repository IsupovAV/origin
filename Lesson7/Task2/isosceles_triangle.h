#pragma once

#include "triangle.h"

// Равнобедренный треугольник
class IsoscelesTriangle : public Triangle {
public:
  IsoscelesTriangle(int a, int b, int A, int B);

  // Полный конструктор для проверки работы исключений
  IsoscelesTriangle(int a, int b, int c, int A, int B, int C);

  std::string get_name() override;

  std::string check() override;

};
