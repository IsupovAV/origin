#pragma once
#include "vehicle_air.h"

// класс "Ботинки-вездеходы"
namespace race {

class Broom : public VehicleAir {
public:
  Broom();
  double GetTime(double distance) const override;
  
  std::string GetName() const override;

  TypeVecihle GetType() const override;

};

} // namespace race
