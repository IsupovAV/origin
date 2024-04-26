#pragma once

#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

/*
  Для решения задачи использовал следующие материалы:
  http://e-maxx.ru/algo/big_integer, https://habr.com/ru/articles/172285/
*/
class big_integer {
public:
  // Конструкторы
  big_integer() : digits_(1, 0), is_negative_(false) {}
  big_integer(std::string str);
  big_integer(long long ll);
  big_integer(big_integer const &other); // конструктор копирования
  big_integer(big_integer &&other) noexcept; // конструктор перемещения

  big_integer &operator=(big_integer &&) noexcept; // перемещающее присваивание
  big_integer &operator=(big_integer const &); // копирующее присваивание

  // операторы
  friend std::ostream &operator<<(std::ostream &os, const big_integer &bi);
  friend bool operator==(const big_integer &lhs, const big_integer &rhs);
  friend bool operator<(const big_integer &lhs, const big_integer &rhs);
  friend bool operator!=(const big_integer &lhs, const big_integer &rhs);
  friend bool operator<=(const big_integer &lhs, const big_integer &rhs);
  friend bool operator>(const big_integer &lhs, const big_integer &rhs);
  friend bool operator>=(const big_integer &lhs, const big_integer &rhs);
  friend const big_integer operator+(big_integer lhs, const big_integer &rhs);
  friend const big_integer operator-(big_integer lhs, const big_integer &rhs);
  friend const big_integer operator*(const big_integer &lhs,
                                     const big_integer &rhs);
  friend const big_integer operator*(const long long &lhs,
                                     const big_integer &rhs);
  friend const big_integer operator*(const big_integer &lhs,
                                     const long long &rhs);

  // унарный плюс
  const big_integer operator+() const { return *this; }

  // унарный минус
  const big_integer operator-() const {
    big_integer copy(*this);
    copy.is_negative_ = !is_negative_;
    return copy;
  }

  operator std::string() const; // Преобразование в строку

private:
  void remove_leading_zeros_();
  void check_number_(const std::string_view &str);

  static const int BASE = 1'000'000'000; // основание системы счисления
  std::vector<int> digits_; // внутреннее хранилище числа
  bool is_negative_;        // знак числа
};
