#include "thread_pool.h"

static void func1() {
  std::cout << "function: " << __FUNCTION__ << " worked completely"
            << std::endl;
}

static void func2() {
  std::cout << "function: " << __FUNCTION__ << " worked completely"
            << std::endl;
}

static void func3() {
  std::cout << "function: " << __FUNCTION__ << " worked completely"
            << std::endl;
}

static void func4() {
  std::cout << "function: " << __FUNCTION__ << " worked completely"
            << std::endl;
}

int main() {
  const int hw_threads = std::thread::hardware_concurrency();
  const int count_submits = 10;

  std::vector<task> vector_of_tasks{func1, func2, func3, func4};
  thread_pool pool{hw_threads};

  std::jthread thread1(&thread_pool::submit, &pool, vector_of_tasks,
                      count_submits);

  return 0;
}

