#include "parallelogram.h"

Parallelogram::Parallelogram(int a, int b, int A, int B)
  : Quadrangle(a, b, a, b, A, B, A, B) {
  name = "Параллелограмм";
  std::string msg = check();
  if(!msg.empty()) {
    throw GeometricException(msg);
  }

}

Parallelogram::Parallelogram(int a, int b, int c, int d, int A, int B, int C, int D)
  : Quadrangle(a, b, c, d, A, B, C, D) {
  name = "Параллелограмм";
  std::string msg = check();
  if(!msg.empty()) {
    throw GeometricException(msg);
  }
}



std::string Parallelogram::get_name()  { return name; }

std::string Parallelogram::check()  {
  std::string reason = Quadrangle::check();
  if(get_side('a') != get_side('c') || get_side('b') != get_side('d'))
    reason = "стороны попарно не равны ";
  if(get_angle('A') != get_angle('C') || get_angle('B') != get_angle('D'))
    reason += "углы попарно не равны ";
  return reason;
}
