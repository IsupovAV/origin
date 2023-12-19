#include <iostream>
#include <string>

// Чтобы протестировать использовал кодировку UTF8 для исходных файлов .сpp,
// а запускал готовый .exe - файл используя gitbush

class Counter {
public:
  Counter(int new_count) : count_(new_count) {}
  Counter() : count_(1) {}  
  void Inc() { 
    ++count_;
  }
  void Dec() { 
    --count_;
  }
  int GetCount() { 
    return count_;
  }

private:
  int count_;
};

void TestCounter(int start) {
  char op = 0;

  Counter cnt(start);
  while (op != 'x') {
    std::cout << "Введите команду ('+', '-', '=' или 'x'): ";
    std::cin >> op;
    switch (op) {
    case '+':
      cnt.Inc();
      break;
    case '-':
      cnt.Dec();
      break;
    case '=':
      std::cout << cnt.GetCount() << '\n';
      break;
    default:
      break;
    }
  }

  std::cout << "До свидания!" << std::endl;
}

int main() { 
  std::string yes_no;
  std::cout << "Вы хотите указать начальное значение счётчика? Введите да или нет: ";
  std::cin >> yes_no;

  int start_count = 1;
  if (yes_no == "да") {
    std::cout << "Введите начальное значение счётчика: ";
    std::cin >> start_count;
  }
  
  TestCounter(start_count);

  return 0; 
}
