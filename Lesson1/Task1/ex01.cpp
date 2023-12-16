#include <iostream>
#include <string>

enum class Month {
  Jan = 1,
  Feb,
  Mar,
  Apr,
  May,
  Jun,
  Jul,
  Aug,
  Sep,
  Oct,
  Nov,
  Dec
};

int main() {
  // Чтобы протестировать использовал кодировку UTF8 для исходных файлов .сpp,
  // а запускал готовый .exe - файл используя gitbush командной строки.
  // setlocale(LC_ALL, "Russian");
  int num_month;
  Month month;
  while (true) {
    std::cout << "Введите номeр месяца: ";
    std::cin >> num_month;
    if (num_month == 0) {
      std::cout << "До свидания" << std::endl;
      break;
    }
    month = static_cast<Month>(num_month);
    switch (month) {
    case Month::Jan:
      std::cout << "Январь\n";
      break;
    case Month::Feb:
      std::cout << "Февраль\n";
      break;
    case Month::Mar:
      std::cout << "Март\n";
      break;
    case Month::Apr:
      std::cout << "Апрель\n";
      break;
    case Month::May:
      std::cout << "Май\n";
      break;
    case Month::Jun:
      std::cout << "Июнь\n";
      break;
    case Month::Jul:
      std::cout << "Июль\n";
      break;
    case Month::Aug:
      std::cout << "Август\n";
      break;
    case Month::Sep:
      std::cout << "Сентябрь\n";
      break;
    case Month::Oct:
      std::cout << "Октябрь\n";
      break;
    case Month::Nov:
      std::cout << "Ноябрь\n";
      break;
    case Month::Dec:
      std::cout << "Декабрь\n";
      break;
    default:
      std::cout << "Неправильный номер!\n";
      break;
    }
  }

  return 0;
}
