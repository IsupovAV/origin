#include <fstream>
#include <iostream>
#include <string>

class Address {
public:
  Address(const std::string &city, const std::string &street,
          int house, int flat)
      : city_(city), street_(street), house_(house), flat_(flat) {}

  std::string GetOutputAddress() const{
    return city_ + ", " + street_ + ", " + std::to_string(house_) + ", " +
           std::to_string(flat_);
  }

private:
  std::string city_;
  std::string street_;
  int house_;
  int flat_;
};

typedef Address* AddressPtr; // указатель на Address

void ReadFile(std::ifstream& inp, AddressPtr* &arr, int n) {
  std::string city;
  std::string street;
  int house;
  int flat;
  for (int i = 0; i < n; ++i) {
    inp >> city >> street >> house >> flat;
    arr[i] = new Address(city, street, house, flat);
  }
}

void WriteFile(AddressPtr* &arr, int n) {
  std::ofstream out("out.txt");
  for (int i = n - 1; i >= 0; --i) {
    out << arr[i]->GetOutputAddress() << std::endl;
  }

  out.close();
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

  WriteFile(arr, n);

  for (int i = 0; i < n; ++i) {
    delete arr[i];
  }

  delete[] arr;

  return 0;
}
