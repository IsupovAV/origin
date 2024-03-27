#include <iostream>
#include <random>
#include <variant>
#include <vector>

std::variant<int, std::string, std::vector<int>> get_variant() {
  std::mt19937 engine;
  std::random_device device;
  engine.seed(device());
  std::uniform_int_distribution<unsigned> distribution(0, 2);
  const unsigned random_variable = distribution(engine);

  std::variant<int, std::string, std::vector<int>> result;
  switch (random_variable) {
    case 0:
      result = 5;
      break;
    case 1:
      result = "string";
      break;
    case 2:
      result = std::vector<int>{1, 2, 3, 4, 5};
      break;
    default:
      break;
  }
  return result;
}

void print_vector(const std::vector<int> &v) {
  for (const auto &e: v)
    std::cout << e << ' ';
  std::cout << '\n';
}

void test(int n = 10) {
  while (n--) {
    auto res = get_variant();
    if (std::holds_alternative<int>(res))
      std::cout << std::get<int>(res) << '\n';
    else if (std::holds_alternative<std::string>(res))
      std::cout << std::get<std::string>(res) << '\n';
    else
      print_vector(std::get<std::vector<int>>(res));
  }
}

int main() {
  test();

  return 0;
}
