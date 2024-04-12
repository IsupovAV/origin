#include <iostream>
#include <list>
#include <set>
#include <vector>

template<class T>
void print_container(T &container, const std::string &spacing = " ") {
  auto it = container.cbegin();
  std::cout << *it++;
  while (it != container.cend()) {
    std::cout << spacing << *it++;
  }
  std::cout << std::endl;
}

int main() {
  {
    std::set<std::string> test_set = {"one", "two", "three", "four"};
    print_container(test_set);// four one three two

    std::list<std::string> test_list = {"one", "two", "three", "four"};
    print_container(test_list, ", ");// one, two, three, four

    std::vector<std::string> test_vector = {"one", "two", "three", "four"};
    print_container(test_vector, ", ");// one, two, three, four
  }
  std::cout << std::endl;

  {
    std::set<int> test_set = {4, 3, 1, 2};
    print_container(test_set);

    std::list<int> test_list = {4, 3, 2, 1};
    print_container(test_list, ", ");

    std::vector<double> test_vector = {4.3, -3, 2.01, 0.314};
    print_container(test_vector, ", ");
  }

  return 0;
}
