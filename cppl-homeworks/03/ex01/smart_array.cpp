#include <stdexcept>

#include "smart_array.h"

smart_array::smart_array(const int capacity) : size_(0), capacity_(capacity > 0 ? capacity : 1) {
  data_ = new int[capacity_];
}

smart_array::~smart_array() { delete[] data_; }

void smart_array::add_element(const int el) {
  if (size_ >= capacity_) // нужно увеличить вместимость массива
  {
    resize_();
  }
  data_[size_++] = el;
}

[[nodiscard]] int smart_array::get_element(const int index) const {
  if (size_ <= index || index < 0)
    throw std::out_of_range("выход за пределы массива");
  return data_[index];
}

int smart_array::operator[](const int index) const { return get_element(index); }

void smart_array::resize_() {
  capacity_ = 2 * size_;
  const auto temp = new int[capacity_];
  for (int i = 0; i < size_; ++i)
    temp[i] = data_[i];

  delete[] data_;
  data_ = temp;
}

int smart_array::get_size() const {
  return size_;
}

int smart_array::get_capacity() const {
  return capacity_;
}

