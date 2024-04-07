#include <exception>
#include <iostream>
#include <random>

double get_random() {
  std::random_device r;
  std::default_random_engine e(r());
  std::uniform_real_distribution<double> uniform_dist(1.0, 17.0);
  return uniform_dist(e);
}

template<class T>
class Table {
public:
  Table(int row, int col) : row_(row), col_(col) {
    CreateTable_();
  }

  Table(const Table &table) {
    row_ = table.row_;
    col_ = table.col_;
    CreateTable_();
    DeepCopy_(table);
  }

  ~Table() {
    DeleteStorage_();
  }

  [[nodiscard]] int GetRow() const {
    return row_;
  }

  [[nodiscard]] int GetCol() const {
    return col_;
  }

  [[nodiscard]] int Size() const {
    return row_ * col_;
  }

  // Взял отсюда
  // https://stackoverflow.com/questions/6969881/operator-overload-for-two-dimensional-array
  struct Proxy_ {
    T *_array;

    Proxy_(T *_array) : _array(_array) {}

    T &operator[](int index) {
        return _array[index];
    }

  };

  Proxy_ operator[](const int index) const {
    return Proxy_(storage_[index]);
  }

  Proxy_ operator[](const int index) {
    return Proxy_(storage_[index]);
  }

  Table& operator=(const Table &table) {
    if (this == &table)
      return *this;
    DeleteStorage_();
    row_ = table.row_;
    col_ = table.col_;
    CreateTable_();
    DeepCopy_(table);

    return *this;
  }

private:
  int row_;
  int col_;
  T **storage_;

  void CreateTable_() {
    storage_ = new T *[row_] {};
    for (int i = 0; i < row_; ++i) {
      storage_[i] = new T[col_]{};
    }
  }

  void DeepCopy_(const Table &table) {
    for (int i = 0; i < row_; ++i) {
      for (int j = 0; j < col_; ++j) {
        storage_[i][j] = table[i][j];
      }
    }
  }

  void DeleteStorage_(){
    for (int i = 0; i < row_; ++i) {
      delete[] storage_[i];
    }
    delete[] storage_;
  }
};

template<class T>
void print_table(const Table<T> &table) {
  int n = table.GetRow();
  int m = table.GetCol();
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      std::cout << table[i][j] << ' ';
    }
    std::cout << std::endl;
  }
}

int main() {
#ifdef _WIN32
  system("chcp 65001");
#endif // _WIN32

  auto test = Table<int>(2, 3);
  test[0][0] = 4;
  std::cout << "Проверил присваивание test[0][0] = 4: " << test[0][0] << std::endl;
  std::cout << "Общее количество элементов Table<int>[2][3]: " << test.Size() << std::endl;

  auto test1 = Table<double>(3, 4);

  for (int i = 0; i < test1.GetRow(); ++i) {
    for (int j = 0; j < test1.GetCol(); ++j) {
      test1[i][j] = get_random();
    }
  }
  std::cout << "\nИсходный массив test1:\n";
  print_table(test1);
  std::cout << std::endl;

  // Проверил конструктор копирования
  auto test2(test1);
  std::cout << "Массив полученный конструтором копирования test2(test1):\n";
  print_table(test2);
  std::cout << std::endl;

  std::cout << "Исходный массив test3:\n";
  auto test3 = Table<double>(3, 3);
  int n = test3.GetRow(), m = test3.GetCol();
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      test3[i][j] = (i + 1) * (j + 1);
    }
  }
  print_table(test3);
  std::cout << std::endl;

  // Проверка оператора присваивания
  test2 = test3;
  std::cout << "Массив полученный через оператор присваивания test2 = test3:\n";
  print_table(test2);
  std::cout << std::endl;

  return 0;
}
