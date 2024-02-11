#include <cmath>
#include "camel.h"

namespace race {

Camel::Camel() { 
  kind_name = "Верблюд"; 
  type_ = TypeVecihle::GROUND;
}

double race::Camel::GetTime(double distance) const { 
  double time = distance / CAMEL_SPEED;
  int count_rest = std::ceil(time / CAMEL_BEFORE_REST) - 1;
  if (count_rest > 0) {
    time += CAMEL_FIRST_REST;
    time += --count_rest * CAMEL_DEFAULT_REST;
  }
  
  return time;
}

std::string Camel::GetName() const { return kind_name; }

TypeVecihle Camel::GetType() const { return type_; }

} // namespace race
