#include "eagle.h"

namespace race {
Eagle::Eagle() { 
  kind_name = "Орёл"; 
  type_ = TypeVecihle::AIR;
}

double Eagle::GetTime(double distance) const { 
  return (distance * GetDRF(EAGLE_DRF)) / EAGLE_SPEED;
}

std::string Eagle::GetName() const { return kind_name; }

TypeVecihle Eagle::GetType() const { return type_; }

} // namespace race
