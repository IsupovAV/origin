#pragma once
#include "vehicle_air.h"

// класс "Ковёр-самолёт"
namespace race {
class FlyingCarpet : public VehicleAir {
public:
  FlyingCarpet();

  double GetTime(double distance) const override;

  std::string GetName() const override;

  TypeVecihle GetType() const override;

};

} // namespace race