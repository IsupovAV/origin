#pragma once

#include "figure.h"

#ifdef QUADRANGLE_EXPORTS
#define QUADRANGLE_API __declspec(dllexport)
#else
#define QUADRANGLE_API __declspec(dllimport)
#endif

// Произвольный четырёхугольник
class QUADRANGLE_API Quadrangle : public Figure {
public:
  Quadrangle(int a, int b, int c, int d, int A, int B, int C, int D);

  std::string get_name() override;

  // side: 'a' - сторона a_, 'b' - сторона b_, 'c' - сторона c_, , 'd' - сторона d_
  int get_side(char side) override;
  // angle: 'A' - угол A_, 'B' - угол B_, 'С' - угол C_, 'D' - угол D_
  int get_angle(char angle) override;

  // для печати сторон и углов
  std::string dump_sides() override;
  std::string dump_angles() override;


private:
  int a_, b_, c_, d_; // длины сторон
  int A_, B_, C_, D_; // углы
};
