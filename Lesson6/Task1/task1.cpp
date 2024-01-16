#include <iostream>

// #define MODE 0
#define MODE 1
// #define MODE 5

int main() {

#ifndef MODE
#error Ошибка, определите костанту MODE
#endif

#if MODE == 0
  std::cout << "Работаю в режиме тренировки" << std::endl;
#elif MODE == 1
  std::cout << "Работаю в боевом режиме" << std::endl;
  int a, b;
  std::cout << "Введите число 1: ";
  std::cin >> a;
  std::cout << "Введите число 2: ";
  std::cin >> b;
  std::cout << "Результат сложения: " << a + b << std::endl;
#else
  std::cout << "Неизвестный режим. Завершение работы" << std::endl;
#endif

  return 0;
}
