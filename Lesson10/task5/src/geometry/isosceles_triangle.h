#pragma once

#include "triangle.h"

// Равнобедренный треугольник
class IsoscelesTriangle : public Triangle {
public:
  IsoscelesTriangle(int a, int b, int A, int B);

  std::string get_name() override;
};
