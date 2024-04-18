/*
Нужно создать упрощённый аналог std::unique_ptr.
В шаблонном классе должны быть реализованы функции:
1. Конструктор, принимающий сырой указатель.
2. Перегружен оператор * для получения объекта.
3. Запрещены оператор присваивания и конструктор копирования.
4. Метод release, который освобождает владение и возвращает сырой указатель.
5. Деструктор.
*/
#include <iostream>
#include <vector>

#include "simple_unique_ptr.h"

int main(int argc, char *argv[]) {
#ifdef _WIN32
  system("chcp 65001");
#endif// _WIN32

  simple_unique_ptr<std::vector<int>> ptr { new std::vector<int> { 1, 2, 3, 4, 5 } };
	
	std::cout << (*ptr)[4] << std::endl;
 
  return 0;
}
