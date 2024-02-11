#include "broom.h"

namespace race {

Broom::Broom() { 
  kind_name = "Метла"; 
  type_ = TypeVecihle::AIR;
}

double Broom::GetTime(double distance) const {
  int percentage = static_cast<int>(distance) / 1000 * BROOM_DRF_PER1000;
  return (distance * GetDRF(percentage)) / BROOM_SPEED;
}

std::string Broom::GetName() const { return kind_name; }

TypeVecihle Broom::GetType() const { return type_; }

} // namespace race