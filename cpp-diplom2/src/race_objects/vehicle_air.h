#pragma once
#include "vehicle.h"

// класс воздушные транспортные средства
namespace race {
class VehicleAir : public Vehicle {
protected:
  double GetDRF(double percentage) const;
};
}
