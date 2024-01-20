#include "triangle.h"

Triangle::Triangle(int a, int b, int c, int A, int B, int C)
  : Figure(three_sides), a_(a), b_(b), c_(c), A_(A), B_(B), C_(C) {
  name = "Треугольник";
  std::string msg = check();
  if(!msg.empty()) {
    throw GeometricException(msg);
  }

}

std::string Triangle::get_name() { return name; }

// side: 'a' - сторона a_, 'b' - сторона b_, 'c' - сторона c_
int Triangle::get_side(const char side)  {
  int ret = 0;
  switch (side) {
    case 'a': ret = a_;
    break;
    case 'b': ret = b_;
    break;
    case 'c': ret = c_;
    break;
    default:
      break;
  }
  return ret;
};

// angle: 'A' - угол A_, 'B' - угол B_, 'С' - угол C_
int Triangle::get_angle(const char angle)  {
  int ret = 0;
  switch (angle) {
    case 'A': ret = A_;
    break;
    case 'B': ret = B_;
    break;
    case 'C': ret = C_;
    break;
    default:
      break;
  }
  return ret;
};

std::string Triangle::dump_sides()  {
  return "a=" + std::to_string(a_) + " b=" + std::to_string(b_) +
         " c=" + std::to_string(c_);
}

std::string Triangle::dump_angles()  {
  return "A=" + std::to_string(A_) + " B=" + std::to_string(B_) +
         " C=" + std::to_string(C_);
}


std::string Triangle::check() {
  std::string reason;
  if(A_ + B_ + C_ != 180)
    reason = "сумма углов не равна 180 ";
  else if(get_sides_count() != 3)
    reason = "у фигуры не 3 стороны ";
  return reason;
}

std::string Triangle::dump_description() {
  std::string result = get_name() + " (стороны " + std::to_string(a_) + ", " +
    std::to_string(b_) + ", " + std::to_string(c_) + "; углы " +
      std::to_string(A_) + ", " + std::to_string(B_) + ", " + std::to_string(C_) + ") ";
  return result;
}


