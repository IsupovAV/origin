#pragma once
#include <iostream>

template<class T>
class simple_vector {
public:
  explicit simple_vector(const size_t capacity) : size_(0), capacity_(capacity > 0 ? capacity : 1) {
    data_ = new T[capacity_];
  }

  explicit simple_vector() : size_(0), capacity_(1) {
    data_ = new T[capacity_];
  }

  simple_vector(simple_vector<T> &src) {
    size_ = src.size_;
    capacity_ = src.capacity_;
    data_ = new T[capacity_];
    for(int i = 0; i < size_; ++i)
      data_[i] = src[i];
  }

  ~simple_vector() {
    delete[] data_;
  }

  void push_back(const T &element) {
    if (size_ >= capacity_) {
      resize_();
    }
    data_[size_++] = element;
  }

  T at(const int ind){
    if(ind < 0 || ind >= size_) throw std::runtime_error("out of range");
    return data_[ind];
  }

  T operator[](const int ind) const{
    return data_[ind];
  }

  T& operator[](const int ind){
    return data_[ind];
  }

  size_t size(){
    return size_;
  }

  size_t capacity(){
    return capacity_;
  }

private:
  void resize_() {
    capacity_ = 2 * size_;
    T *new_data = new T[capacity_];
    for (int i = 0; i < size_; ++i) new_data[i] = data_[i];
    delete[] data_;
    data_ = new_data;
  }

  T *data_ = nullptr;
  size_t size_;
  size_t capacity_;
};
