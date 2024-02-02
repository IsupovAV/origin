#include "pch.h"
#include "quadrangle.h"

Quadrangle::Quadrangle(int a, int b, int c, int d, int A, int B, int C, int D)
  : Figure(four_sides), a_(a), b_(b), c_(c), d_(d), A_(A), B_(B), C_(C),
    D_(D) {
  name = "Четырёхугольник";
}

std::string Quadrangle::get_name()  { return name; }

// side: 'a' - сторона a_, 'b' - сторона b_, 'c' - сторона c_, , 'd' - сторона d_
int Quadrangle::get_side(char side)  {
  int ret = 0;
  switch (side) {
    case 'a': ret = a_;
    break;
    case 'b': ret = b_;
    break;
    case 'c': ret = c_;
    break;
    case 'd': ret = d_;
    break;
    default:
      break;
  }
  return ret;
};

// angle: 'A' - угол A_, 'B' - угол B_, 'С' - угол C_, 'D' - угол D_
int Quadrangle::get_angle(char angle) {
  int ret = 0;
  switch (angle) {
    case 'A': ret = A_;
    break;
    case 'B': ret = B_;
    break;
    case 'C': ret = C_;
    break;
    case 'D': ret = D_;
    break;
    default:
      break;
  }
  return ret;
};

std::string Quadrangle::dump_sides() {
  return "a=" + std::to_string(a_) + " b=" + std::to_string(b_) +
         " c=" + std::to_string(c_) + " d=" + std::to_string(d_);
}

std::string Quadrangle::dump_angles() {
  return "A=" + std::to_string(A_) + " B=" + std::to_string(B_) +
         " C=" + std::to_string(C_) + " D=" + std::to_string(D_);
}

