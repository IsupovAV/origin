#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <string>

std::ostream& operator<<(std::ostream& out, const std::vector<std::pair<char, int>>& v){
  std::cout << "[OUT]:\n";
  for(const auto& p: v){
    out << p.first << ": " << p.second << '\n';
  }
  return out;
}

void symbols_frequency(const std::string& in, std::vector<std::pair<char, int>>& v){
  std::map<char, int> m;
  // собираем словарь, упорядочен по значению ключей
  for(const auto& e: in) ++m[e];
  // словарь копируем в вектор пар <char, int>
  v.assign(m.begin(), m.end());

  // сортируем по убыванию второго значения пары
  std::sort(v.begin(), v.end(),
            [](const std::pair<char, int>& lhs, const std::pair<char, int>& rhs)
            {
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
