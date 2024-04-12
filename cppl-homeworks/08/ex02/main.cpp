#include <iostream>
#include <list>
#include <set>
#include <vector>

template<class T>
void print_container(const T &container, const std::string& spacing = " ") {
  bool first = true;
  for (const auto &e: container) {
    if (first) {
      first = false;
    } else {
      std::cout << spacing;
    }
    std::cout << e;
  }
  std::cout << std::endl;
}

int main() {
  std::set<std::string> test_set = {"one", "two", "three", "four"};
  print_container(test_set);// four one three two

  std::list<std::string> test_list = {"one", "two", "three", "four"};
  print_container(test_list, ", ");// one, two, three, four

  std::vector<std::string> test_vector = {"one", "two", "three", "four"};
  print_container(test_vector, ", ");// one, two, three, four

  return 0;
}
