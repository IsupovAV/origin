#include <fstream>
#include <iostream>
#include <string>

class Address {
public:
  Address(const std::string &city, const std::string &street, int house,
          int flat)
      : city_(city), street_(street), house_(house), flat_(flat) {}

  std::string GetOutputAddress() const {
    return city_ + ", " + street_ + ", " + std::to_string(house_) + ", " +
           std::to_string(flat_);
  }

  // геттер для city_
  std::string GetCity() { return city_; }

private:
  std::string city_;
  std::string street_;
  int house_;
  int flat_;
};

typedef Address *AddressPtr; // указатель на Address

void ReadFile(std::ifstream &inp, AddressPtr *&arr, int n) {
  std::string city;
  std::string street;
  int house;
  int flat;
  for (int i = 0; i < n; ++i) {
    inp >> city >> street >> house >> flat;
    arr[i] = new Address(city, street, house, flat);
  }
}

void WriteFile(AddressPtr *&arr, int n) {
  std::ofstream out("out.txt");
  for (int i = n - 1; i >= 0; --i) {
    out << arr[i]->GetOutputAddress() << std::endl;
  }
  out.close();
}

void Swap(AddressPtr &a, AddressPtr &b) {
  AddressPtr tmp = a;
  a = b;
  b = tmp;
}

// Сортировка пузырьком
// https://www.geeksforgeeks.org/bubble-sort/
void BubbleSort(AddressPtr *&arr, int n) {
  for (int i = 0; i < n - 1; ++i) {
    bool swapped = false;
    for (int j = 0; j < n - i - 1; ++j) {
      if (arr[j]->GetCity() < arr[j + 1]->GetCity()) {
        Swap(arr[j], arr[j + 1]);
        swapped = true;
      }
    }
    if (!swapped)
      break;
  }
}

// Быструю сортировку взял отсюда
// https://www.geeksforgeeks.org/cpp-program-for-quicksort/
int Partition(AddressPtr *&arr, int start, int end) {

  auto pivot = arr[start]->GetCity();

  int count = 0;
  for (int i = start + 1; i <= end; i++) {
    if (arr[i]->GetCity() > pivot)
      count++;
  }

  int pivot_index = start + count;
  Swap(arr[pivot_index], arr[start]);

  // Сортироуем левую и правую части от pivot-элемента
  int i = start, j = end;

  while (i < pivot_index && j > pivot_index) {

    while (arr[i]->GetCity() > pivot) {
      i++;
    }

    while (arr[j]->GetCity() <= pivot) {
      j--;
    }

    if (i < pivot_index && j > pivot_index) {
      Swap(arr[i++], arr[j--]);
    }
  }

  return pivot_index;
}

void QuickSort(AddressPtr *&arr, int start, int end) {

  // Сортировка закончена
  if (start >= end)
    return;

  // делим массив на части
  int p = Partition(arr, start, end);

  // Сортируем левую часть
  QuickSort(arr, start, p - 1);

  // Сортируем правую часть
  QuickSort(arr, p + 1, end);
}

int main() {
  int n = 0;

  std::ifstream inp("in.txt");
  if (!inp.is_open()) {
    std::cout << "файл in.txt не найден!\n";
    return 1;
  }

  inp >> n;
  auto *arr = new AddressPtr[n];

  ReadFile(inp, arr, n);
  inp.close();

  BubbleSort(arr, n);
  //QuickSort(arr, 0, n - 1);

  WriteFile(arr, n);

  for (int i = 0; i < n; ++i) {
    delete arr[i];
  }

  delete[] arr;

  return 0;
}
