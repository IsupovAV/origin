#pragma once

class smart_array {
public:
  explicit smart_array(int capacity);

  ~smart_array();

  void add_element(int el);

  [[nodiscard]] int get_element(int index) const;

  int operator[](int index) const;

  smart_array(const smart_array &) = delete; // конструктор копирования, запрещен
  smart_array &operator=(const smart_array &) = delete; // оператор присваивания, запрещен

  [[nodiscard]] int get_size() const;

  [[nodiscard]] int get_capacity() const;

private:
  void resize_(); // изменить размер массива

  int *data_ = nullptr; // указатель на массив int
  int size_ = 0; // текущий размер массива
  int capacity_ = 0; // емкость массива
};
