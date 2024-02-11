#include "vehicle_air.h"

namespace race {

  // полцчить "Коэффициент сокращения расстояния"
  double VehicleAir::GetDRF(double percentage) const { return (100.0 - percentage) / 100.0; }

} // namespace race
