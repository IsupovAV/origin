#include <iostream>
#include "leaver.h"

int main()
{
  system("chcp 1251");
  setlocale(LC_ALL, "Russian");
  Leaver lv;
  std::cout << "������� ��� : ";
  std::string name;
  std::cin >> name;
  std::cout << lv.leave(name) << std::endl;

  return 0;
}
