#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

class functor_counter {
public:
  functor_counter() = default;

  void operator()(const int x) {
    if (x % 3 == 0) {
      ++count_;
      sum_ += x;
    }
  }

  [[nodiscard]] int get_count() const {
    return count_;
  }

  [[nodiscard]] int get_sum() const {
    return sum_;
  }

private:
  int count_ = 0;
  int sum_ = 0;
};

int main() {
  std::vector<int> v{4, 1, 3, 6, 25, 54};

  auto print_vector = [](const int &n) { std::cout << n << ' '; };
  std::cout << "[IN]: ";
  std::for_each(std::begin(v), std::end(v), print_vector);
  std::cout << std::endl;

  std::string h1 = "[OUT]: get_sum() = ";
  std::string h2 = "[OUT]: get_count() = ";
  // Используем функтор functor_counter()
  std::cout << h1 << std::for_each(std::begin(v), std::end(v), functor_counter()).get_sum() << std::endl;
  std::cout << h2 << std::for_each(std::begin(v), std::end(v), functor_counter()).get_count() << std::endl;
  std::cout << std::endl;

  // То же через лямбды
  std::cout << h1 << std::accumulate(std::begin(v), std::end(v), 0,
[](int s, const int e) { return s + (e % 3 == 0) * e; }) << std::endl;
  std::cout << h2 << std::count_if(std::begin(v), std::end(v),
    [](const int &e) { return e % 3 == 0; }) << std::endl;

  return 0;
}
