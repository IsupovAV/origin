#pragma once

#include <ostream>

class smart_array {
public:
  explicit smart_array(int capacity); // конструктор
  // Нужно перегрузить конструктор копирования. Иначе конструктор
  // копирования, созданный по умолчанию, присвоит указатель
  // правого объекта - левому.
  // Поэтому нужно перегрузить конструктор, так что бы мы получили
  // два разных объекта, поэлементно копируя правый в левый.
  smart_array(const smart_array &source); // конструктор копированя

  ~smart_array();

  void add_element(int el);

  [[nodiscard]] int get_element(int index) const;

  int operator[](int index) const;

  // Нужно перегрузить оператор присваивания. Иначе оператор
  // присваивания, созданный по умолчанию, присвоит указатель
  // правого объекта - левому. Тем самым мы получим один объект
  // с двумя разными именами, а левый объект будет утерян.
  // Поэтому нужно перегрузить оператор, так что бы мы получили
  // два разных объекта, поэлементно копируя правый в левый.
  smart_array &operator=(const smart_array &source);

  [[nodiscard]] int get_size() const;

  [[nodiscard]] int get_capacity() const;

private:
  void resize_(); // изменить размер массива

  int *data_ = nullptr; // указатель на массив int
  int size_ = 0; // текущий размер массива
  int capacity_ = 0; // емкость массива
};

// Перегрузил оператор << для smart_array
inline std::ostream& operator<<(std::ostream &out, const smart_array& arr) {
  const int sz = arr.get_size();
  for(int i = 0; i < sz; ++i)
    out << arr[i] << ' ';
  out << std::endl;
  return out;
}