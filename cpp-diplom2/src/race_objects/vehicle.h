#pragma once
#include <iostream>
#include "constants.h"

// абстрактный класс "транспортные средства"
namespace race {
class Vehicle {
public:
  virtual double GetTime(double distance) const = 0;
  virtual std::string GetName() const =0;
  virtual TypeVecihle GetType() const = 0;

protected:
  std::string kind_name;	// наименование вида транспортного средства: верблюд, метла и т.д.
  TypeVecihle type_;			// тип транспортного средства: наземные, воздушные
};

} // namespace race
