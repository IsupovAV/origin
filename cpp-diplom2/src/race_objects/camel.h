#pragma once
#include "vehicle_land.h"

// класс "Верблюд"
namespace race {

class Camel : public VehicleLand {
public:
  Camel();
  double GetTime(double distance) const override;
  
  std::string GetName() const override;

  TypeVecihle GetType() const override;

};

} // namespace race
