#pragma once
#include <condition_variable>
#include <functional>
#include <iostream>
#include <mutex>
#include <queue>

template <class T> class safe_queue {
public:
  void push(T work) {
    std::unique_lock<std::mutex> lck(mt_);
    queue_tasks_.push(work);
    cv_.notify_one();
  };
  
  T pop() {
    std::unique_lock<std::mutex> lck(mt_);
    cv_.wait(lck, [this]() { return !queue_tasks_.empty(); });
    T work = std::move(queue_tasks_.front());
    queue_tasks_.pop();
    return work;
  };
  
  int size() {
    std::unique_lock<std::mutex> lck(mt_);
    return queue_tasks_.size();
  };

  bool empty() {
    std::unique_lock<std::mutex> lck(mt_);
    return queue_tasks_.empty();
  }

  void front() {
    std::unique_lock<std::mutex> lck(mt_);
    queue_tasks_.front()();
  };

private:
  std::queue<T> queue_tasks_;
  std::mutex mt_;
  std::condition_variable cv_;
};
