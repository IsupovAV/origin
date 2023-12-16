#include <iostream>
#include <string>

// Чтобы протестировать использовал кодировку UTF8 для исходных файлов .сpp,
// а запускал готовый .exe - файл используя gitbush командной строки.

struct Address {
  Address(const std::string &city, const std::string &street, int house,
          int flat, int ind)
      : city{city}, street{street}, num_house{house}, num_flat{flat},
        index{ind} {
  }

  std::string city;
  std::string street;
  int num_house{0};
  int num_flat{0};
  int index{0};
};

void print_address(const Address& addr) { 
  std::cout << "Город: " << addr.city << "\n";
  std::cout << "Улица: " << addr.street << "\n";
  std::cout << "Номер дома: " << addr.num_house << "\n";
  std::cout << "Номер квартиры: " << addr.num_flat << "\n";
  std::cout << "Индекс: " << addr.index << "\n";
  std::cout << std::endl;
}

int main() { 
  Address addr1 = Address("Москва", "Арбат", 12, 8, 123456);
  Address addr2 = Address("Ижевск", "Пушкина", 59, 143, 953769);

  print_address(addr1);
  print_address(addr2);

  return 0;
}
