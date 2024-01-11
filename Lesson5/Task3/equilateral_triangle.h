#pragma once

#include "triangle.h"

// Равносторонний треугольник
class EquilateralTriangle : public Triangle {
public:
  explicit EquilateralTriangle(int a);

  std::string get_name() override;
};
