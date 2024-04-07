#include <exception>
#include <iostream>
#include <random>

// для заполнения массива
double get_random() {
  std::random_device r;
  std::default_random_engine e(r());
  std::uniform_real_distribution<double> uniform_dist(1.0, 17.0);
  return uniform_dist(e);
}

// как объяснял на лекции преподователь
template<class T>
class TWrapper {
public:
  TWrapper(T* arr, const int n): n_(n){
    arr_ = arr;
  }

  T& operator[](int i) {
    if (i < 0 || i >= n_)
      throw std::runtime_error("Выход за пределы массива");
    return arr_[i];
  }

private:
  int n_;
  T* arr_;
};

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


  TWrapper<T> operator[](const int index) const {
    if(index < 0 || index >= row_){
      throw std::runtime_error("Выход за пределы массива");
    }
    TWrapper<T> result(storage_[index], col_);
    return result;
  }

  TWrapper<T> operator[](const int index) {
    if(index < 0 || index >= row_){
      throw std::runtime_error("Выход за пределы массива");
    }
    TWrapper<T> result(storage_[index], col_);

    return result;
  }

  Table &operator=(const Table &table) {
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

  void DeleteStorage_() {
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
#endif// _WIN32

  auto test = Table<int>(2, 3);
  test[0][0] = 4;
  std::cout << "Проверил присваивание test[0][0] = 4: " << test[0][0] << std::endl;

	std::cout << std::endl;
  // Смотрим исключение по первому индексу
  try{
    test[5][8] = 0;
  }catch(std::runtime_error& e){
    std::cout << e.what() << " строки" <<  std::endl;
  }

  // Смотрим исключение по второму индексу
  try{
    test[1][8] = 0;
  }catch(std::runtime_error& e){
    std::cout << e.what() << " столбцы" << std::endl;
  }

	std::cout << std::endl;
  std::cout << "Общее количество элементов Table<int>[2][3]: " << test.Size() << std::endl;

  auto test1 = Table<double>(3, 4);

  int n = test1.GetRow();
  int m = test1.GetCol();
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      test1[i][j] = get_random();
    }
  }
  std::cout << "\nИсходный массив test1:\n";
  print_table(test1);
  std::cout << std::endl;

  // Проверил конструктор копирования
  auto test2(test1);
  std::cout << "Массив полученный конструктором копирования test2(test1):\n";
  print_table(test2);
  std::cout << std::endl;

  std::cout << "Исходный массив test3:\n";
  auto test3 = Table<double>(3, 3);
  n = test3.GetRow();
  m = test3.GetCol();
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      test3[i][j] = get_random();
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