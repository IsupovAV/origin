#pragma once
#include "safe_queue.h"
#include <chrono>
#include <thread>
#include <vector>

using namespace std::chrono_literals;

using task = std::function<void()>;

class thread_pool {
public:
  thread_pool(int cores);
  ~thread_pool();
  void submit(std::vector<task> vector_functions, int count_submits);
  void work();

private:
  std::mutex mt_;
  std::vector<std::thread> threads_;
  safe_queue<task> safe_queue_tasks_;
  bool is_submit_ = false;
};
