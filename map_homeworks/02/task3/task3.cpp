// task3.cpp : Защищенный обмен данными
#include <iostream>
#include <mutex>
#include <utility>
#include <windows.h>

class Data {
public:
  explicit Data(int value) : data_(value) {}

  int GetData() const { return data_; }

  void SetData(int value) { data_ = value; }

  std::mutex &GetMutex() { return mutex_; }

private:
  int data_;
  std::mutex mutex_;
};

// используем lock
static void swap_lock(Data &a, Data &b) {
  std::lock(a.GetMutex(), b.GetMutex());
  std::lock_guard<std::mutex> lock_a(a.GetMutex(), std::adopt_lock);
  std::lock_guard<std::mutex> lock_b(b.GetMutex(), std::adopt_lock);

  int temp = a.GetData();
  a.SetData(b.GetData());
  b.SetData(temp);
}

// используем scoped_lock
static void swap_scoped_lock(Data &a, Data &b) {
  std::scoped_lock lock(a.GetMutex(), b.GetMutex());

  int temp = a.GetData();
  a.SetData(b.GetData());
  b.SetData(temp);
}

// используем unique_lock
static void swap_unique_lock(Data &a, Data &b) {
  std::unique_lock<std::mutex> lock_a(a.GetMutex(), std::defer_lock);
  std::unique_lock<std::mutex> lock_b(b.GetMutex(), std::defer_lock);
  std::lock(lock_a, lock_b);

  int temp = a.GetData();
  a.SetData(b.GetData());
  b.SetData(temp);
}

static void test_swap(const std::string &method) {
  Data d1(7);
  Data d2(-23);

  std::cout << "Используем \"" << method << "\"" <<  std::endl;
  std::cout << "Значения до обмена: d1 = " << d1.GetData()
            << ", d2 = " << d2.GetData() << std::endl;

  if (method == "lock") {
    swap_lock(d1, d2);
  } else if (method == "scoped_lock") {
    swap_scoped_lock(d1, d2);
  } else if ((method == "unique_lock")) {
    swap_unique_lock(d1, d2);
  }

  std::cout << "Значения после обмена: d1 = " << d1.GetData()
            << ", d2 = " << d2.GetData() << "\n\n";
}

int main(int argc, char **argv) {
  system("chcp 65001");

  test_swap("lock");

  test_swap("scoped_lock");

  test_swap("unique_lock");

  return 0;
}