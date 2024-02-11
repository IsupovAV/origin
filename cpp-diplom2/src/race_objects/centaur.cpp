#include "centaur.h"

namespace race {
Centaur::Centaur() { 
  kind_name = "Кентавр"; 
  type_ = TypeVecihle::GROUND;
}

double Centaur::GetTime(double distance) const { 
  double time = distance / CENTAUR_SPEED;
  int count_rest = std::ceil(time / CENTAUR_BEFORE_REST) - 1;
  time += CENTAUR_DEFAULT_REST * count_rest;
  return time;
}

std::string Centaur::GetName() const { return kind_name; }

TypeVecihle Centaur::GetType() const { return type_; }

}
