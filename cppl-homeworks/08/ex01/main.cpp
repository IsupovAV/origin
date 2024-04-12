#include <algorithm>
#include <iostream>
#include <vector>
#include <string>

template <class T>
void print(std::vector<T>& v, const std::string& header){
  std::cout << header;
  for (const auto& i : v)
    std::cout << i << ' ';
  std::cout << '\n';
}

template <class T>
void unique_vector(std::vector<T>& v){
  std::sort(v.begin(), v.end());
  auto last = std::unique(v.begin(), v.end());
  v.erase(last, v.end());
}

int main() {
  {
    std::vector<int> v{2, 3, 1, 1, 2, 1, 1, 3, 3, 3, 4, 5, 4};

    print(v, "before unique_vector: ");
    unique_vector(v);
    print(v, "after unique_vector: ");
    std::cout << std::endl;
  }

  {
    std::vector<std::string> v{"bbb", "aa", "bbb", "aa", "cccc", "cccc"};
    print(v, "before unique_vector: ");
    unique_vector(v);
    print(v, "after unique_vector: ");
  }

  return 0;
}
