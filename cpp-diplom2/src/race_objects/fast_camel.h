#pragma once
#include "vehicle_land.h"

// класс "Верблюд-быстроход"
namespace race {
class FastCamel : public VehicleLand {
public:
  FastCamel();
  double GetTime(double distance) const override;

  std::string GetName() const override;

  TypeVecihle GetType() const override;

};

}
