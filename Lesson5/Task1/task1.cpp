#include <iostream>

#include "calculator.h"

int main() {
  double a, b;
  std::cout << "Введите первое число: ";
  std::cin >> a;
  std::cout << "Введите второе число: ";
  std::cin >> b;
  std::cout << "Выберите операцию (1 - сложение, 2 вычитание, 3 - умножение, 4 - деление, 5 - возведение в степень): ";
  char op = ' ';
  std::cin >> op;
  double res = 0;
  switch (op) {
    case
    '1':
      res = add(a, b);
      std::cout << a << " + " << b << " = " << res << std::endl;
      break;
    case '2':
      res = sub(a, b);
      std::cout << a << " - " << b << " = " << res << std::endl;
      break;
    case '3':
      res = mul(a, b);
      std::cout << a << " * " << b << " = " << res << std::endl;
      break;
    case '4':
      res = division(a, b);
      std::cout << a << " / " << b << " = " << res << std::endl;
      break;
    case '5':
      res = power(a, b);
      std::cout << a << " в степени " << b << " = " << res << std::endl;
      break;
    default:
      break;
  }

  return 0;
}
