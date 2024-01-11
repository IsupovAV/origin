#pragma once

#include "triangle.h"

// Прямоугольный треугольник
class RightTriangle : public Triangle {
public:
  RightTriangle(int a, int b, int c, int A, int B);

  std::string get_name() override;
};
