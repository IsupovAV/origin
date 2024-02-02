#pragma once

#include "triangle.h"

#ifdef RIGHT_TRIANGLE_EXPORTS
#define RIGHT_TRIANGLE_API __declspec(dllexport)
#else
#define RIGHT_TRIANGLE_API __declspec(dllimport)
#endif

// Прямоугольный треугольник
class RIGHT_TRIANGLE_API RightTriangle : public Triangle {
public:
  RightTriangle(int a, int b, int c, int A, int B);

  std::string get_name() override;
};
