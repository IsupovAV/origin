#include <iostream>

#include "tester.h"
#include "counter.h"

void TestCounter(const int start) {
  Counter cnt(start);
  char op = 0;
  do {
    switch (op) {
      case '+':
        cnt.Inc();
      break;
      case '-':
        cnt.Dec();
      break;
      case '=':
        std::cout << cnt.GetCount() << std::endl;
      break;
      default:
        break;
    }
    std::cout << "Введите команду ('+', '-', '=' или 'q' для выхода): ";
    std::cin >> op;

  }while(op != 'q');

  std::cout << "До свидания!" << std::endl;
}

