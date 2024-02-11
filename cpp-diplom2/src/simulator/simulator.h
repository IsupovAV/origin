#pragma once
#include <algorithm>
#include <sstream>
#include <vector>

#include "constants.h"
#include "vehicle.h"
#include "boots.h"
#include "broom.h"
#include "camel.h"
#include "centaur.h"
#include "eagle.h"
#include "fast_camel.h"
#include "flying_carpet.h"

namespace race {
class Simulator {
public:
  bool ExecuteSimulation(); // запуск симулятора

private:
  void Calculate_(); // расчет для зарегистрированных тс
  bool IsContinueSimulation_(); // ещё проводим гонку
  void Registration_(std::string &header1, std::string &header2,
                     std::string &header3); // регистрация тс для гонки
  TypeRace ChooseRaceType_(); // выбор типа гонки (земля, воздух, оба)
  double InputDistance_(); // ввод дистанции
  void ShowResults_();     // показать результат гонки

  // вспомогательные функции
  void ShowRegistrationHeader_(
      const std::string &header1, const std::string &header2,
      const std::string
          &header3); // показать верхние три строки в зависимости от ситуации
  void ShowRegistrationDef_(); // показать основное меню выбора тс
  Vehicle *GetChoice_(
      int choice); // возвращает тс в зависимоти от выбора из меню регистрации
  std::string WhoRegistration_(); // возвращает строку текущих зарегистрированных тс
  bool IsStartRace_(); // можно ли начать гонку и меню
  bool CheckTypeRace_(Vehicle *v); // контроль типа гонки
  void ClearRegistration_(); // очистка данных регистрации
  bool AlreadyRegistered_(Vehicle *v); // проверка существует ли тс в списке зарегистрированных
  void LessThanTwo_(); // меню для случая, когда зарегистрировано менее двух тс

  // переменные
  TypeRace type_race_; // тип текущей гонки
  double distance_;    // дистанция текущей гонки
  std::vector<const Vehicle *> vehicles_; // вектоор для хранения указателей на зарегистрированные тс
  std::vector<std::pair<std::string, double>> results_; // вектор пар результатов гонки, "наимекнование тс, время
                // прохождения дистанции"
};

} // namespace race
