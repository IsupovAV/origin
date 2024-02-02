#pragma once

#include "figure.h"

#ifdef TRIANGLE_EXPORTS
#define TRIANGLE_API __declspec(dllexport)
#else
#define TRIANGLE_API __declspec(dllimport)
#endif

// Произвольный треугольник
class TRIANGLE_API Triangle : public Figure {
public:
  Triangle(int a, int b, int c, int A, int B, int C);
  std::string get_name() override;
  // side: 'a' - сторона a_, 'b' - сторона b_, 'c' - сторона c_
  int get_side(char side) override;
  // angle: 'A' - угол A_, 'B' - угол B_, 'С' - угол C_
  int get_angle(char angle) override;

  // для вывода на печать сторон и углов
  std::string dump_sides() override;
  std::string dump_angles() override;

private:
  int a_, b_, c_;
  int A_, B_, C_;
};
