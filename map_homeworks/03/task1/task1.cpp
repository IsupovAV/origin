// task1.cpp : Сортировка выбором
#include <algorithm>
#include <chrono>
#include <exception>
#include <future>
#include <iostream>
#include <random>
#include <thread>
#include <vector>

using namespace std;

template <typename T> void print_vector(vector<T> &v) {
  for (rsize_t i = 0; i < v.size(); ++i) {
    cout << v[i] << ' ';
  }
  cout << endl;
}

// Функция генерации целочисленного вектора размерностью n случайных
// чисел равномерного распределения в диапазоне от -range до range
std::vector<int> random_vector_int(int range, int n) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<int> dist(-range, range);
  std::vector<int> result;
  while(n-- > 0) {
    result.push_back(dist(gen));
  }
  return result;
}

// Функция генерации вещественного вектора размерностью n случайных
// чисел равномерного распределения в диапазоне от -range до range
std::vector<double> random_vector_double(int range, int n) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<double> dist(-range, range);
  std::vector<double> result;
  while (n-- > 0) {
    result.push_back(dist(gen));
  }
  return result;
}

template <typename T, typename Iterator>
void find_min(Iterator beg, Iterator end, Iterator vbeg, promise<T> prom) {
  Iterator min_it = min_element(beg + 1, end);
  prom.set_value(static_cast<int>(min_it - vbeg));
}

template <typename T, typename Iterator>
void selection_sort(vector<T> &v, Iterator beg, Iterator end) {
  auto vbeg = v.begin();
  for (Iterator it = vbeg; it < v.end() - 1; ++it) {
    promise<T> prom;
    future<T> future_result = prom.get_future();
    auto async_min = async(launch::async, find_min<T, Iterator>, it, v.end(),
                           vbeg, move(prom));
    auto min = static_cast<int>(future_result.get());
    auto ind = static_cast<int>(it - vbeg);
    if (v[min] < v[ind])
      swap(v[min], v[ind]);
  }
}

int main() {
  // vector<int> v{4, -5, 15, 16, -1, 3, 7, 4, 10, 18, 1, 0, 9, 8, 5, 5};
  vector<int> v = random_vector_int(50, 20);
  cout << "Begore sort" << endl;
  print_vector(v);
  selection_sort(v, begin(v), end(v));
  cout << "\nAfter sort" << endl;
  print_vector(v);
  cout << endl;

  // vector<double> v1{1.2, -11.4, 5.015, -11.41, 4.0, 65.07, 3.14, 17.897};
  vector<double> v1 = random_vector_double(10, 10);
  cout << "Begore sort" << endl;
  print_vector(v1);
  selection_sort(v1, begin(v1), end(v1));
  cout << "\nAfter sort" << endl;
  print_vector(v1);
  cout << endl;

  return 0;
}
