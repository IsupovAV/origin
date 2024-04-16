#pragma once

template<class T>
class simple_unique_ptr {
public:
  explicit simple_unique_ptr(T *ptr) : raw_pointer_{ptr} {
  }

  simple_unique_ptr()
      : raw_pointer_{nullptr} {
  }

  // Нет конструктора копирования и присваивания
  simple_unique_ptr(const simple_unique_ptr &) = delete;
  simple_unique_ptr &operator=(const simple_unique_ptr &) = delete;

  ~simple_unique_ptr() {
    delete raw_pointer_;
    raw_pointer_ = nullptr;
  }

  const T *get() const {
    return raw_pointer_;
  }

  void reset() {
    delete raw_pointer_;
    raw_pointer_ = nullptr;
  }
  void reset(T *ptr) {
    delete raw_pointer_;
    raw_pointer_ = ptr;
  }

  T *release() {
    T *tmp{raw_pointer_};
    raw_pointer_ = nullptr;
    return tmp;
  }

  const T &operator*() const {
    return *(raw_pointer_);
  }

  T *operator->() const {
    return raw_pointer_;
  }

  explicit operator bool() const {
    return raw_pointer_ != nullptr;
  }

private:
  T *raw_pointer_;
};

template<typename T>
simple_unique_ptr<T> make_unique(const T &n) {
  return simple_unique_ptr<T>{new T{n}};
}
