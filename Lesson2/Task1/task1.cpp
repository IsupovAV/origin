#include <iostream>

class Calculator {
public:
  double add() { return num1 + num2; }
  double multiply() { return num1 * num2; }
  double subtract_1_2() { return num1 - num2; }
  double subtract_2_1() { return num2 - num1; }
  double divide_1_2() { return num1 / num2; }
  double divide_2_1() { return num2 / num1; }
  bool set_num1(double num1) {
    if(num1 != 0)
      this->num1 = num1;
    return num1 != 0;
  }
  bool set_num2(double num2) {
    if(num2 != 0)
      this->num2 = num2;
    return num2 != 0;
  }

private:
  double num1;
  double num2;
};

void InputArguments(Calculator &calc) {
  double a, b;
  std::cout << "Введите num1: ";
  std::cin >> a;
  while (!calc.set_num1(a)) {
    std::cout << "Неверный ввод!\n";
    std::cout << "Введите num1: ";
    std::cin >> a;
  }

  std::cout << "Введите num2: ";
  std::cin >> b;
  while (!calc.set_num2(b)) {
    std::cout << "Неверный ввод!\n";
    std::cout << "Введите num2: ";
    std::cin >> b;
  }
}

void PrintResult(Calculator &calc) {
  std::cout << "num1 + num2 = " << calc.add() << std::endl;
  std::cout << "num1 - num2 = " << calc.subtract_1_2() << std::endl;
  std::cout << "num2 - num1 = " << calc.subtract_2_1() << std::endl;
  std::cout << "num1 * num2 = " << calc.multiply() << std::endl;
  std::cout << "num1 / num2 = " << calc.divide_1_2() << std::endl;
  std::cout << "num2 / num1 = " << calc.divide_2_1() << std::endl;
}

void TestCalculatorWork() {
  Calculator calc{};
  InputArguments(calc);
  PrintResult(calc);
}

int main() {
  while (true) {
    TestCalculatorWork();
  }

  return 0;
}
