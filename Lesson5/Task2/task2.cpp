#include <iostream>
#include <string>

#include "tester.h"

int main() {
  std::string yes_no;
  std::cout << "Вы хотите указать начальное значение счётчика? Введите да или нет: ";
  std::cin >> yes_no;

  int start_count = 1;
  if (yes_no == "да") {
    std::cout << "Введите начальное значение счётчика: ";
    std::cin >> start_count;
  }

  TestCounter(start_count);

  return 0;
}
