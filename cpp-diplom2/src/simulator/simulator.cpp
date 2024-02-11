#include "simulator.h"

namespace race {

bool Simulator::ExecuteSimulation() {
  type_race_ = ChooseRaceType_();
  distance_ = InputDistance_();

  std::string header1, header2, header3;
  header2 = (type_race_ == TypeRace::GROUND_RACE
                 ? "Гонка для наземного транспорта. "
                 : (type_race_ == TypeRace::AIR_RACE
                        ? "Гонка для воздушного транспорта. "
                        : "Гонка для наземного и воздушного транспорта. "));
  std::ostringstream os;
  os << distance_;
  header2 += "Расстояние: " + os.str();
  do {
    header1 = "";
    Registration_(header1, header2, header3);
  } while (!IsStartRace_());
  Calculate_();
  ShowResults_();
  ClearRegistration_();

  return IsContinueSimulation_();
}

void Simulator::Calculate_() {
  results_.clear();
  for (const auto &item : vehicles_) {
    results_.push_back({item->GetName(), item->GetTime(distance_)});
  }
}

bool Simulator::IsContinueSimulation_() {
  std::cout << "1. Провести ещё одну гонку\n";
  std::cout << "2. Выйти\n";
  int choice = 0;
  while (choice < 1 || 2 < choice) {
    std::cout << "Выберите действие: ";
    std::cin >> choice;
  }
  std::cout << std::endl;
  return choice == 1;
}

TypeRace Simulator::ChooseRaceType_() {
  std::cout << "1. Гонка для наземного транспорта\n";
  std::cout << "2. Гонка для воздушного транспорта\n";
  std::cout << "3. Гонка для наземного и воздушного транспорта\n";

  int choice = 0;
  while (choice > 3 || choice < 1) {
    std::cout << "Выберите тип гонки (1 - 3): ";
    std::cin >> choice;
  }

  std::cout << std::endl;

  return TypeRace(choice);
}

double Simulator::InputDistance_() {
  double distance = 0;
  while (distance <= 0) {
    std::cout << "Укажите длину дистанции (должна быть положительна): ";
    std::cin >> distance;
  }
  std::cout << std::endl;

  return distance;
}

void Simulator::ShowResults_() {
  std::cout << "Результаты гонки: " << std::endl;
  sort(begin(results_), end(results_),
       [](const std::pair<std::string, double> &a,
          const std::pair<std::string, double> &b) {
         return a.second < b.second;
       });
  for (int i = 0; i < results_.size(); ++i) {
    std::cout << i + 1 << ". " << results_[i].first << ". "
              << "Время: " << results_[i].second << '\n';
  }
  std::cout << std::endl;
}

void Simulator::ShowRegistrationHeader_(const std::string &header1,
                                        const std::string &header2,
                                        const std::string &header3) {
  if (header1.length() > 0)
    std::cout << header1 << std::endl;
  if (header2.length() > 0)
    std::cout << header2 << std::endl;
  if (header3.length() > 0)
    std::cout << header3 << std::endl;
}

Vehicle *Simulator::GetChoice_(int choice) {
  Vehicle *ptr{};
  if (choice == 1)
    ptr = new Boots();
  else if (choice == 2)
    ptr = new Broom();
  else if (choice == 3)
    ptr = new Camel();
  else if (choice == 4)
    ptr = new Centaur();
  else if (choice == 5)
    ptr = new Eagle();
  else if (choice == 6)
    ptr = new FastCamel();
  else if (choice == 7)
    ptr = new FlyingCarpet();
  return ptr;
}

std::string Simulator::WhoRegistration_() {
  if (vehicles_.size() == 0)
    return {};
  std::string s = "Зарегистрированные транспортные средства: ";
  bool first = true;
  for (const auto &it : vehicles_) {
    if (first) {
      s += it->GetName();
      first = false;
    } else {
      s += ", " + it->GetName();
    }
  }

  return s;
}

void Simulator::ShowRegistrationDef_() {
  std::cout << "1. Ботинки-вездеходы\n";
  std::cout << "2. Метла\n";
  std::cout << "3. Верблюд\n";
  std::cout << "4. Кентавр\n";
  std::cout << "5. Орёл\n";
  std::cout << "6. Верблюд-быстроход\n";
  std::cout << "7. Ковёр-самолёт\n";
  std::cout << "0. Закончить регистрацию\n";
}

bool Simulator::IsStartRace_() {
  int choice = -1;
  if (vehicles_.size() >= 2) {
    std::cout << "1. Зарегистрировать транспорт\n";
    std::cout << "2. Начать гонку\n";
    while (choice > 2 || choice < 1) {
      std::cout << "Выберите действие: ";
      std::cin >> choice;
    }
    std::cout << std::endl;
  } else {
    LessThanTwo_();
  }

  return choice == 2;
}

bool Simulator::CheckTypeRace_(Vehicle *v) {
  bool ret = true;
  TypeVecihle type = v->GetType();
  if (type_race_ == TypeRace::GROUND_RACE) {
    ret = (type == TypeVecihle::GROUND);
  } else if (type_race_ == TypeRace::AIR_RACE) {
    ret = (type == TypeVecihle::AIR);
  }

  return ret;
}

void Simulator::ClearRegistration_() {
  for (const auto &item : vehicles_)
    delete item;
  vehicles_.clear();
}

bool Simulator::AlreadyRegistered_(Vehicle *v) {
  std::string name = v->GetName();
  for (const auto &item : vehicles_) {
    if (name == item->GetName())
      return true;
  }
  return false;
}

void Simulator::LessThanTwo_() {
  std::cout << "Должно быть зарегистрировано хотя бы 2 транспортных средства\n";
  std::cout << "1. Зарегистрировать транспорт\n";
  int choice = 0;
  while (choice != 1) {
    std::cout << "Выберите действие: ";
    std::cin >> choice;
  }
  std::cout << std::endl;
}

void Simulator::Registration_(std::string &header1, std::string &header2,
                              std::string &header3) {
  int choice = -1;
  while (choice != 0) {
    ShowRegistrationHeader_(header1, header2, header3);
    ShowRegistrationDef_();
    while (choice > 7 || choice < 0) {
      std::cout
          << "Выберите транспорт или 0 для окончания процесса регистрации: ";
      std::cin >> choice;
    }
    std::cout << std::endl;
    if (choice > 0) {
      Vehicle *veh = GetChoice_(choice);
      bool already_registered = AlreadyRegistered_(veh);
      if (!already_registered && CheckTypeRace_(veh)) {
        vehicles_.push_back(veh);
        header1 = veh->GetName() + " успешно зарегистрирован!";
      } else if (!already_registered && !CheckTypeRace_(veh)) {
        header1 =
            "Попытка зарегиcтрировать неправильный тип транспортного средства!";
        delete veh;
      } else if (already_registered) {
        header1 = veh->GetName() + " уже зарегистрирован!";
        delete veh;
      }
      choice = -1;
    }
    header3 = WhoRegistration_();
  }
}
} // namespace race
