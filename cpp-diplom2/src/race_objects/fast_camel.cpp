#include "fast_camel.h"

namespace race {

FastCamel::FastCamel() { 
  kind_name = "Верблюд-быстроход"; 
  type_ = TypeVecihle::GROUND;
}

double FastCamel::GetTime(double distance) const {
  double time = distance / FAST_CAMEL_SPEED;
  int count_rest = std::ceil(time / FAST_CAMEL_BEFORE_REST) - 1;
  if (count_rest > 0) {
    time += CAMEL_FIRST_REST;
  }

  if (--count_rest > 0) {
    time += FAST_CAMEL_SECOND_REST;
    time += --count_rest * FAST_CAMEL_DEFAULT_REST;
  }

  return time;
}

std::string FastCamel::GetName() const { return kind_name; }

TypeVecihle FastCamel::GetType() const { return type_; }

} // namespace race
