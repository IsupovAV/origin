#pragma once
#include "vehicle_land.h"

// класс "Кентавр"
namespace race {
class Centaur : public VehicleLand {
public:
  Centaur();
  double GetTime(double distance) const override;

  std::string GetName() const override;

  TypeVecihle GetType() const override;

};
} // namespace race
