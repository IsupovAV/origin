// task2.cpp : for_each (параллельный вариант)
#include <algorithm>
#include <chrono>
#include <exception>
#include <future>
#include <iostream>
#include <numeric>
#include <random>
#include <thread>
#include <vector>

using namespace std;

template <typename T> void print_vector(const vector<T> &v) {
  for (auto it = v.begin(); it < v.end(); ++it) {
    cout << *it << ' ';
  }
  cout << endl;
}

int constexpr size_minimal_piece = 2;

template <typename Iterator, typename Function>
void par_for_each(Iterator first, Iterator last, Function &&func) {
  auto size = distance(first, last);
  if (size <= size_minimal_piece) {
    for_each(first, last, func);
  } else {
    Iterator middle = first;
    advance(middle, size / 2);
    async(std::launch::async,
          [first, middle, &func]() { par_for_each(first, middle, func); });
    async(std::launch::async,
          [middle, last, &func]() { par_for_each(middle, last, func); });
  }
}

int main() {
  vector<int> v{20, 5, 15, 20, 48, 65, 11, 10, 8, 2, 17, 13, 14};

  cout << "Before \"par_for_each\"\n";
  print_vector(v);

  // возвели в квадрат
  auto squaring = [](int &k) { k = k * k; };
  par_for_each(v.begin(), v.end(), squaring);

  cout << "\nAfter \"par_for_each\" (squaring)\n";
  print_vector(v);

  // извлекли корень
  auto root_extraction = [](int &k) { k = sqrt(k); };
  par_for_each(v.begin(), v.end(), root_extraction);

  cout << "\nAfter \"par_for_each\" (root extraction)\n";
  print_vector(v);

  return 0;
}
