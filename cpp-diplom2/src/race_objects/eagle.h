#pragma once
#include "vehicle_air.h"

// класс "Орёл"
namespace race {
class Eagle : public VehicleAir {
public:
  Eagle();

  double GetTime(double distance) const override;

  std::string GetName() const override;
    
  TypeVecihle GetType() const override;

};

} // namespace race
