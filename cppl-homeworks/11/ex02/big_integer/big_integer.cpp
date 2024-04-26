#include "big_integer.h"

// Конструкторы
// из строки, представляющей длинное число
big_integer::big_integer(std::string str) {
  if (str.length() == 0) {
    // из пустой строки создается ноль
    *this = big_integer();
    return;
  }

  is_negative_ = str[0] == '-' ? true : false;
  if (is_negative_) {
    str = str.substr(1);
  }

  check_number_(str);

  for (long long i = str.length(); i > 0; i -= 9) {
    if (i < 9)
      this->digits_.push_back(atoi(str.substr(0, i).c_str()));
    else
      this->digits_.push_back(atoi(str.substr(i - 9, 9).c_str()));
  }

  // удалим из числа ведущие нули, если они есть
  remove_leading_zeros_();
}

// из числа
big_integer::big_integer(long long ll) {
  is_negative_ = ll < 0 ? true : false;
  if (is_negative_) {
    ll = -ll;
  }

  do {
    digits_.push_back(ll % big_integer::BASE);
    ll /= big_integer::BASE;
  } while (ll != 0);
}

// Копирования
big_integer::big_integer(const big_integer &other) {
  is_negative_ = other.is_negative_;
  std::copy(other.digits_.begin(), other.digits_.end(),
            std::back_inserter(digits_));
}

// Перемещения
big_integer::big_integer(big_integer &&other) noexcept
    : digits_(std::move(other.digits_)),
      is_negative_(std::move(other.is_negative_)) {}

// Операторы присваивания
// перемещающее присваивание
big_integer &big_integer::operator=(big_integer &&rhs) noexcept {
  std::swap(digits_, rhs.digits_);
  std::swap(is_negative_, rhs.is_negative_);
  return *this;
}

// копирующее присваивание
big_integer &big_integer::operator=(big_integer const &rhs) {
  if (this != &rhs) {
    digits_ = rhs.digits_;
    is_negative_ = rhs.is_negative_;
  }
  return *this;
}

// Перегрузка оператора <<
std::ostream &operator<<(std::ostream &os, const big_integer &bi) {
  if (bi.digits_.empty()) {
    os << 0;
    return os;
  }

  if (bi.is_negative_)
    os << '-';
  os << bi.digits_.back();
  // следующие числа нам нужно печатать группами по 9 цифр
  // поэтому сохраним текущий символ-заполнитель, а потом восстановим его
  char old_fill = os.fill('0');
  for (long long i = static_cast<long long>(bi.digits_.size()) - 2; i >= 0;
       --i) {
    os << std::setw(9) << bi.digits_[i];
  }

  os.fill(old_fill);

  return os;
}

// Преобразование в строку
big_integer::operator std::string() const {
  std::stringstream ss;
  ss << *this;
  return ss.str();
}

// Операторы сравнения
bool operator==(const big_integer &lhs, const big_integer &rhs) {
  // числа разных знаков точно не равны
  if (lhs.is_negative_ != rhs.is_negative_)
    return false;
  // поскольку у нас два представления нуля, нужно это особо обработать
  bool empty1 =
      rhs.digits_.empty() || (rhs.digits_.size() == 1 && rhs.digits_[0] == 0);
  bool empty2 =
      lhs.digits_.empty() || (lhs.digits_.size() == 1 && lhs.digits_[0] == 0);
  if (empty1 && empty2)
    return true;
  else
    return false;

  // так как у нас нет ведущих нулей, то в числах должно быть одинаковое
  // количество цифр (разрядов)
  if (lhs.digits_.size() != rhs.digits_.size())
    return false;

  for (size_t i = 0; i < lhs.digits_.size(); ++i)
    if (lhs.digits_[i] != rhs.digits_[i])
      return false;

  return true;
}

bool operator<(const big_integer &lhs, const big_integer &rhs) {
  if (lhs == rhs)
    return false;

  // одно или оба отрицательные
  if (lhs.is_negative_ && rhs.is_negative_)
    return ((-rhs) < (-lhs));
  if (lhs.is_negative_)
    return false;
  if (rhs.is_negative_)
    return true;

  // оба положительные
  if (lhs.digits_.size() != rhs.digits_.size())
    return lhs.digits_.size() < rhs.digits_.size();

  for (long long i = lhs.digits_.size() - 1; i >= 0; --i) {
    if (lhs.digits_[i] != rhs.digits_[i])
      return lhs.digits_[i] < rhs.digits_[i];
  }

  return false;
}

bool operator!=(const big_integer &lhs, const big_integer &rhs) {
  return !(lhs == rhs);
}

bool operator<=(const big_integer &lhs, const big_integer &rhs) {
  return (lhs < rhs || lhs == rhs);
}

bool operator>(const big_integer &lhs, const big_integer &rhs) {
  return !(lhs <= rhs);
}

bool operator>=(const big_integer &lhs, const big_integer &rhs) {
  return !(lhs < rhs);
}

// Сложение
const big_integer operator+(big_integer lhs, const big_integer &rhs) {
  // разбираемся со знаками операндов
  if (lhs.is_negative_) {
    if (rhs.is_negative_)
      return -(-lhs + (-rhs));
    else
      return rhs - (-lhs);
  } else if (rhs.is_negative_)
    return lhs - (-rhs);

  int carry = 0; // флаг переноса из предыдущего разряда
  for (size_t i = 0;
       i < std::max(lhs.digits_.size(), rhs.digits_.size()) || carry != 0;
       ++i) {
    if (i == lhs.digits_.size())
      lhs.digits_.push_back(0);
    lhs.digits_[i] += carry + (i < rhs.digits_.size() ? rhs.digits_[i] : 0);
    carry = lhs.digits_[i] >= big_integer::BASE;
    if (carry != 0)
      lhs.digits_[i] -= big_integer::BASE;
  }

  return lhs;
}

const big_integer operator-(big_integer lhs, const big_integer &rhs) {
  // разбираемся со знаками операндов
  if (rhs.is_negative_)
    return lhs + (-rhs);
  else if (lhs.is_negative_)
    return -(-lhs + rhs);
  else if (lhs < rhs)
    return -(rhs - lhs);

  int carry = 0;
  for (size_t i = 0; i < rhs.digits_.size() || carry != 0; ++i) {
    lhs.digits_[i] -= carry + (i < rhs.digits_.size() ? rhs.digits_[i] : 0);
    carry = lhs.digits_[i] < 0;
    if (carry != 0)
      lhs.digits_[i] += big_integer::BASE;
  }

  lhs.remove_leading_zeros_();
  return lhs;
}

const big_integer operator*(const big_integer &lhs, const big_integer &rhs) {
  big_integer result;
  result.digits_.resize(lhs.digits_.size() + rhs.digits_.size());
  for (size_t i = 0; i < lhs.digits_.size(); ++i) {
    int carry = 0;
    for (size_t j = 0; j < rhs.digits_.size() || carry != 0; ++j) {
      long long cur =
          result.digits_[i + j] +
          lhs.digits_[i] * 1LL * (j < rhs.digits_.size() ? rhs.digits_[j] : 0) +
          carry;
      result.digits_[i + j] = static_cast<int>(cur % big_integer::BASE);
      carry = static_cast<int>(cur / big_integer::BASE);
    }
  }
  // не забудем про знак
  result.is_negative_ = lhs.is_negative_ != rhs.is_negative_;
  result.remove_leading_zeros_();
  return result;
}

// Умножение на "обычное" число
const big_integer operator*(const long long &lhs, const big_integer &rhs) {
  return big_integer(lhs) * rhs;
}

const big_integer operator*(const big_integer &lhs, const long long &rhs) {
  return rhs * lhs;
}

// Удалить лидирующие нули
void big_integer::remove_leading_zeros_() {
  while (this->digits_.size() > 1 && this->digits_.back() == 0) {
    this->digits_.pop_back();
  }
  // убираем отрицательный нуль
  if (this->digits_.size() == 1 && this->digits_[0] == 0)
    this->is_negative_ = false;
}

// Проверка корректности строчного представления числа
void big_integer::check_number_(const std::string_view &str) {
  if (str.find_first_not_of("0123456789") != std::string::npos)
    // встетились символы отличные от цифр
    throw std::runtime_error("в big_integer могут быть только цифры");
}