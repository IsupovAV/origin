#include <iostream>

int main() {
  std::cout << "Введите имя: ";
  std::string name;
  std::cin >> name;
  std::cout << "Здравствуйте, " << name << "!" << std::endl;

  return 0;
}
