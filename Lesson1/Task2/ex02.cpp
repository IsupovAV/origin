#include <iostream>
#include <string>

// Чтобы протестировать использовал кодировку UTF8 для исходных файлов .сpp,
// а запускал готовый .exe - файл используя gitbush командной строки.

struct Account {
  Account(int acc_num, const std::string &own, double bal)
      : acс_number{acc_num}, owner{own}, balance{bal} {}
  int acс_number;
  std::string owner;
  double balance;
};

void change_balance(Account &acc, double new_balance) {
  acc.balance = new_balance;
}

int main() {
  int num;
  std::cout << "Введите номер счёта: ";
  int number;
  std::cin >> number;
  std::cout << "Введите имя владельца: ";
  std::string owner;
  std::cin >> owner;
  std::cout << "Введите баланс: ";
  double bal;
  std::cin >> bal;

  auto acc = Account(number, owner, bal);

  std::cout << "Введите новый баланс: ";
  double new_bal;
  std::cin >> new_bal;

  change_balance(acc, new_bal);

  std::cout << "Ваш счёт: " << acc.owner << ", " << acc.acс_number << ", "
            << acc.balance << std::endl;

  return 0;
}
