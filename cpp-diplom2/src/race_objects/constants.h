#pragma once

// вспомогательные константы
namespace race {

  enum class TypeVecihle { GROUND, AIR };

enum class KindVehicle {
  CAMEL,
  FAST_CAMEL,
  CENTAUR,
  BOOTS,
  FLYING_CARPET,
  EAGLE,
  BROOM
};

enum class TypeRace { GROUND_RACE = 1, AIR_RACE, GROUN_AND_AIR };

const int CAMEL_SPEED = 10;       
const int CAMEL_BEFORE_REST = 30;
const int CAMEL_FIRST_REST = 5;
const int CAMEL_DEFAULT_REST = 8;

const int FAST_CAMEL_SPEED = 40;
const int FAST_CAMEL_BEFORE_REST = 10;
const int FAST_CAMEL_FIRST_REST = 5;
const double FAST_CAMEL_SECOND_REST = 6.5;
const int FAST_CAMEL_DEFAULT_REST = 8;

const int CENTAUR_SPEED = 15;
const int CENTAUR_BEFORE_REST = 8;
const int CENTAUR_DEFAULT_REST = 2;

const int BOOTS_SPEED = 6;
const int BOOTS_BEFORE_REST = 60;
const int BOOTS_FIRST_REST = 10;
const int BOOTS_DEFAULT_REST = 5;

const int FLYING_CARPET_SPEED = 10;
// DRF - distance reduction factor (Коэффициент сокращения расстояния) в процентах
const int FLYING_CARPET_DRF_LT1000 = 0;           
const int FLYING_CARPET_DRF_LT5000 = 3;
const int FLYING_CARPET_DRF_LT10000 = 10;
const int FLYING_CARPET_DRF_GE10000 = 5;

const int EAGLE_SPEED = 8;
const int EAGLE_DRF = 6;

const int BROOM_SPEED = 20;
const int BROOM_DRF_PER1000 = 1;




} // namespace game
