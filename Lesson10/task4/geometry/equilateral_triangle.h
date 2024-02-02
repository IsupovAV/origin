#pragma once

#include "triangle.h"

#ifdef EQUILATERAL_TRIANGLE_EXPORTS
#define EQUILATERAL_TRIANGLE_API __declspec(dllexport)
#else
#define EQUILATERAL_TRIANGLE_API __declspec(dllimport)
#endif

// Равносторонний треугольник
class EQUILATERAL_TRIANGLE_API EquilateralTriangle : public Triangle {
public:
  explicit EquilateralTriangle(int a);

  std::string get_name() override;
};
