#include "thread_pool.h"

thread_pool::thread_pool(int cores) {
  for (int i = 0; i < cores; ++i) {
    threads_.push_back(std::thread(&thread_pool::work, this));
  }
}

thread_pool::~thread_pool() {
  for (auto &thread : threads_) {
    thread.join();
  }
}

void thread_pool::submit(std::vector<task> vector_functions,
                         int countSubmits) {
  for (int i = 0; i < countSubmits; ++i) {
    for (size_t j = 0; j < vector_functions.size(); ++j) {
      safe_queue_tasks_.push(vector_functions.at(j));
    }
    std::this_thread::sleep_for(1s);
  }
  is_submit_ = true;
}

void thread_pool::work() {
  while (!is_submit_) {
    std::unique_lock<std::mutex> lockMutex(mt_);
    if (!safe_queue_tasks_.empty()) {
      std::cout << "work id: " << std::this_thread::get_id() << std::endl;
      safe_queue_tasks_.front();
      safe_queue_tasks_.pop();
    } else {
      std::this_thread::yield();
    }
    lockMutex.unlock();
  }
}
