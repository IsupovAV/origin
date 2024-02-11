#pragma once
#include "vehicle_land.h"
#include "constants.h"

// класс "Ботинки-вездеходы"
namespace race {
class Boots : public VehicleLand {
public:
  Boots();
  
  double GetTime(double distance) const override;
  
  std::string GetName() const override;

  TypeVecihle GetType() const override;

};

} // namespace race
