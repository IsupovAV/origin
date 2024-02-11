#include "flying_carpet.h"

namespace race {
FlyingCarpet::FlyingCarpet() { 
  kind_name = "Ковёр-самолёт"; 
  type_ = TypeVecihle::AIR;
}

double FlyingCarpet::GetTime(double distance) const {
  double drf;
  if (distance < 1000) {
    drf = GetDRF(FLYING_CARPET_DRF_LT1000);
  } else if (distance < 5000) {
    drf = GetDRF(FLYING_CARPET_DRF_LT5000);
  } else if (distance < 10000) {
    drf = GetDRF(FLYING_CARPET_DRF_LT10000);
  } else {
    drf = GetDRF(FLYING_CARPET_DRF_GE10000);
  }
  return distance * drf / FLYING_CARPET_SPEED;
}

std::string FlyingCarpet::GetName() const { return kind_name; }

TypeVecihle FlyingCarpet::GetType() const { return type_; }

} // namespace race
