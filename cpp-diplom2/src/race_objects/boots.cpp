#include "boots.h"

// класс "Ботинки-вездеходы"
namespace race {

Boots::Boots() { 
  kind_name = "Ботинки-вездеходы"; 
  type_ = TypeVecihle::GROUND;
}

double Boots::GetTime(double distance) const {
  double time = distance / BOOTS_SPEED;
  int count_rest = std::ceil(time / BOOTS_BEFORE_REST) - 1;
  if (count_rest > 0) {
    time += BOOTS_FIRST_REST;
    time += --count_rest * BOOTS_DEFAULT_REST;
  }

  return time;
}

std::string Boots::GetName() const { return kind_name; }

TypeVecihle Boots::GetType() const { return type_; }

} // namespace race
