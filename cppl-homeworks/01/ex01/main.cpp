#include <algorithm>
#include <iostream>
#include <vector>

int main() {
  std::vector<int> v{4, 7, 9, 14, 12};
  auto print = [](const int &e) { std::cout << e << ' '; };
  std::cout << "Входные данные:  ";
  std::for_each(v.begin(), v.end(), print);
  std::cout << '\n';

  std::for_each(v.begin(), v.end(), [](int &e) { e = (e % 2 ? e * 3 : e); });
  std::cout << "Выходные данные:  ";
  std::for_each(v.begin(), v.end(), print);
  std::cout << '\n';

  return 0;
}
