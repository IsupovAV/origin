#pragma once

#include "triangle.h"

#ifdef ISOSCELES_TRIANGLE_EXPORTS
#define ISOSCELES_TRIANGLE_API __declspec(dllexport)
#else
#define ISOSCELES_TRIANGLE_API __declspec(dllimport)
#endif

// Равнобедренный треугольник
class ISOSCELES_TRIANGLE_API IsoscelesTriangle : public Triangle {
public:
  IsoscelesTriangle(int a, int b, int A, int B);

  std::string get_name() override;
};
