#include <fstream>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

template <class T> 
void move(std::vector<T> &from, std::vector<T> &to) {
  to = std::move(from);
}

template <typename T>
void print_container(const T &container, const std::string &delimiter,
                     std::ostream &os = std::cout) {
  std::copy(
      std::begin(container), std::end(container),
      std::ostream_iterator<typename T::value_type>(os, delimiter.c_str()));
}

int main(int argc, char **argv) {

  std::vector<std::string> one = {"test_string1", "test_string2"};
  std::vector<std::string> two;

  std::cout << "Vector one:" << std::endl;
  print_container(one, "\n");
  std::cout << std::endl;

  move(one, two);
  std::cout << "Vector one is empty: " << std::boolalpha << one.empty()
            << std::endl;
  std::cout << "Vector two:" << std::endl;
  print_container(two, "\n");
  return 0;
}
