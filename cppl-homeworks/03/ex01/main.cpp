#include <iostream>
#include <stdexcept>

#include "smart_array.h"

int main() {
  try {
    smart_array arr(5);

    arr.add_element(1);
    arr.add_element(4);
    arr.add_element(155);
    arr.add_element(14);
    arr.add_element(15);
    std::cout << "Емкость массива " << arr.get_capacity() << std::endl;

    std::cout << arr.get_element(0) << std::endl;
    std::cout << arr[2] << std::endl;

    arr.add_element(30);
    std::cout << "Емкость массива " << arr.get_capacity() << std::endl;
    std::cout << arr.get_element(10) << std::endl;
  }
  catch (const std::exception &ex) {
    std::cout << ex.what() << std::endl;
  }

  return 0;
}
