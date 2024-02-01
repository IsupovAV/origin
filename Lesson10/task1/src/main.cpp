#include <iostream>
#include "greeter.h"

int main() {
  setlocale(LC_ALL, "rus");
  std::cout << "¬ведите им€: ";
  std::string name;
  std::cin >> name;
  Greeter grt;
  std::cout << grt.greet(name) << std::endl;

  return 0;
}
