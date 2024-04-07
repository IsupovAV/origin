/*
 * Нужно реализовать шаблонную функцию возведения в квадрат, которая работает не только с
 * простыми числами, но и с векторами. Для этого создайте две реализации шаблонной функции.
 */
#include <iostream>
#include <vector>
#include <algorithm>

template <class T>
T square(T& x){
  return x * x;
}

template <class T>
std::vector<T>& square(std::vector<T>& v){
  std::for_each(std::begin(v), std::end(v), [](T& e){ e *= e;});
  return v;
}

// Полная специализация шаблона для типа std::string
template <>
std::vector<std::string>& square(std::vector<std::string>& v){
  std::for_each(std::begin(v), std::end(v), [](std::string& e){ e += " in squared";});
  return v;
}

template <class T>
std::ostream& operator<<(std::ostream& out, const std::vector<T>& v){
  for(const auto& e: v){
    out << e << ' ';
  }

  return out;
}


int main() {
  int x = 4;
  std::cout << "[IN]: " << x << std::endl;
  std::cout << "[OUT]: " << square<int>(x) << std::endl;
  std::vector<int> v{-1, 4, 8};
  std::cout << "[IN]: " << v << std::endl;
  std::cout << "[OUT]: " << square<int>(v) << std::endl;
  std::cout << std::endl;

  double pi = 3.14159265359;
  std::cout << "[IN]: " << pi << std::endl;
  std::cout << "[OUT]: " << square<double>(pi) << std::endl;
  std::vector<std::string> s{"Petrov", "Ivanov", "Sidorov"};
  std::cout << "[IN]: " << s << std::endl;
  std::cout << "[OUT]: " << square<std::string>(s) << std::endl;
  std::cout << std::endl;

  return 0;
}
