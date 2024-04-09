#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <string>


void read(std::vector<int>& v){
  std::cout << "[IN]:" << '\n';
  int n;
  std::cin >> n;
  // читаем в можество, отсекаем дубликаты
  std::set<int> mset;
  while(n--){
    int elem;
    std::cin >> elem;
    mset.insert(elem);
  }

  // копируем в вектор уже без дубликатов
  v.assign(mset.begin(), mset.end());
}

void print(const std::vector<int>& v){
  std::cout << "[OUT]:\n";
  for(const auto& e: v)
    std::cout << e << std::endl;
}

int main() {
  std::vector<int> v;
  read(v);
  // сортировка по убыванию
  std::sort(v.begin(), v.end(), std::greater());
  print(v);
  return 0;
}
