#include <iostream>
#include <map>
#include <vector>
#include <set>
#include <algorithm>
#include <string>


std::ostream &operator<<(std::ostream &out, const std::vector<std::pair<char, int>> &v) {
  std::cout << "[OUT]:\n";
  for (const auto &p: v) {
    std::cout << p.first << ": " << p.second << '\n';
  }
  return out;
}

/*
 * Здесь задача 1, но сортировка не нарушает порядок следования букв
 * в исходном тексте. Вначале самые частые, если частоты равны, то
 * идут в исходном порядке введённого текста inp.
 */
void symbols_frequency(const std::string &inp, std::vector<std::pair<char, int>> &v) {
  std::map<char, int> mm;
  for(const auto& e: inp) ++mm[e];

  for (const auto e: inp){
    if(std::find(v.begin(), v.end(), std::pair(e, mm[e])) == v.end())
      // если такой пары не было отправляем в массив
      v.push_back({e, mm[e]});
  }
  // перед сортировкой вектор пар выглядит так:
  // {'H',1} {'e',1} {'l',3} {'o',2} {' ',1} {'w', 1} {'r', 1} {'d',1} {'!',2}
  std::sort(v.begin(), v.end(),
                   [](const auto &lhs, const auto &rhs) {
                     return lhs.second > rhs.second;
                   });
}

int main() {
#ifdef _WIN32
  system("chcp 65001");
#endif// _WIN32
  std::cout << "[IN]: ";
  std::string s;
  std::getline(std::cin, s);
  std::vector<std::pair<char, int>> result;
  symbols_frequency(s, result);
  std::cout << result;

  return 0;
}
