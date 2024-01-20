#include "rhombus.h"

Rhombus::Rhombus(int a, int A, int B) : Parallelogram(a, a, A, B) {
  name = "Ромб";
  std::string msg = check();
  if(!msg.empty()) {
    throw GeometricException(msg);
  }
}

Rhombus::Rhombus(int a, int b, int c, int d, int A, int B, int C, int D)
  : Parallelogram(a, b, c, d,  A, B, C, D) {
  name = "Ромб";
  std::string msg = check();
  if(!msg.empty()) {
    throw GeometricException(msg);
  }

}

std::string Rhombus::get_name()  { return name; }

std::string  Rhombus::check() {
  std::string reason = Parallelogram::check();
  if(get_side('a') != get_side('b'))
    reason = "не все стороны равны ";
  if(get_angle('A') != get_angle('C') || get_angle('B') != get_angle('D'))
    reason += "углы попарно не равны ";

  return reason;
}

