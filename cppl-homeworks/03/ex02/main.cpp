#include <iostream>
#include <stdexcept>

#include "smart_array.h"

int main() {
#ifdef _WIN32
  system("chcp 65001");
#endif // _WIN32
	
  smart_array arr(5);
  arr.add_element(1);
  arr.add_element(4);
  arr.add_element(155);

  std::cout << "До присваивания:\n";
  std::cout << arr;


  smart_array new_array(2);
  new_array.add_element(44);
  new_array.add_element(34);
  std::cout << "\nНовый массив:\n";
  std::cout << new_array;

  arr = new_array;

  std::cout << "\nПосле присваивания:\n";
  std::cout << arr;

  return 0;
}
