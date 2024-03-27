#include <cmath>
#include <functional>
#include <iostream>
#include <vector>

void print(const std::vector<double> &angles, const std::vector<std::function<void(const double)>> &functions) {
  std::cout << "[Выходные данные]:\n";
  for (const auto &angle: angles) {
    std::cout << angle << ": ";
    for (const auto &function: functions)
      function(angle);
    std::cout << std::endl;
  }
}

void print_input(std::vector<double>& angles) {
  std::cout << "[Входные данные]: ";
  bool first = true;
  for (auto &d: angles) {
    constexpr double PI = 3.1415926;
    if (first) {
      std::cout << d << " * " << PI << " / " << 180;
      first = false;
    }
    else {
      std::cout << ", " << d << " * " << PI << " / " << 180;
    }
    d = d * PI / 180;
  }
  std::cout << std::endl;
}

int main() {
  std::vector<double> angles{30, 60, 90, 120};

  print_input(angles);

  auto lambda_sin = [](double angle) { std::cout << "sin: " << sin(angle) << " "; };

  auto lambda_cos = [](double angle) { std::cout << "cos: " << cos(angle) << " "; };

  // auto lamba_tan = [](double angle) {
  //   std::cout << "tan: " << tan(angle) << " ";
  // };

  const std::vector<std::function<void(double)>> functions{lambda_sin, lambda_cos};

  print(angles, functions);

  return 0;
}
