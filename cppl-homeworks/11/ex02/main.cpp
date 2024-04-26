#include "big_integer/big_integer.h"

int main() {
  {
    auto number1 = big_integer("114575");
    auto number2 = big_integer("78524");
    auto result = number1 + number2;
    std::cout << "number1 = " << number1 << std::endl;
    std::cout << "number2 = " << number2 << std::endl;
    std::cout << "number1 + number2 = " << result << std::endl;
    std::cout << std::endl;
  }

  {
    auto number1 =
        big_integer("-78512545444000000000000001521254544400000000000000152");
    auto number2 =
        big_integer("78512545444000000000000001521254544400000000000000152");
    auto result = number1 + number2;
    std::cout << "number1 = " << number1 << std::endl;
    std::cout << "number2 = " << number2 << std::endl;
    std::cout << "number1 + number2 = " << result << std::endl;
    std::cout << std::endl;
  }

  {
    auto number1 =
        big_integer("12545444000000000000001521254544400000000000000152");
    auto number2 =
        big_integer("78512545444000000000000001521254544400000000000000152");
    auto result = number1 - number2;
    std::cout << "number1 = " << number1 << std::endl;
    std::cout << "number2 = " << number2 << std::endl;
    std::cout << "number1 - number2 = " << result << std::endl;
    std::cout << std::endl;
  }

  {
    auto number1 =
        big_integer("12545444000000000000001521254544400000000000000152");
    auto number2 =
        big_integer("78512545444000000000000001521254544400000000000000152");
    auto result = number1 * number2;
    std::cout << "number1 = " << number1 << std::endl;
    std::cout << "number2 = " << number2 << std::endl;
    std::cout << "number1 * number2 = " << result << std::endl;
    std::cout << std::endl;
  }

  {
    auto number1 =
        big_integer("-12545444000000000000001521254544400000000000000152");
    auto number2 =
        big_integer("78512545444000000000000001521254544400000000000000152");
    auto result = number1 * number2;
    std::cout << "number1 = " << number1 << std::endl;
    std::cout << "number2 = " << number2 << std::endl;
    std::cout << "number1 * number2 = " << result << std::endl;
    std::cout << std::endl;
  }

  {
    auto number1 =
        big_integer("12545444000000000000001521254544400000000000000152");
    int number2 = -17;
    auto result = number1 * number2;
    std::cout << "number1 = " << number1 << std::endl;
    std::cout << "number2 (int) = " << number2 << std::endl;
    std::cout << "number1 * number2 = " << result << std::endl;
    std::cout << std::endl;
  }

  {
    big_integer number1;
    auto number2 =
        big_integer("78512545444000000000000001521254544400000000000000152");
    auto result = number1 * number2;
    std::cout << "number1 = " << number1 << std::endl;
    std::cout << "number2 = " << number2 << std::endl;
    std::cout << "number1 * number2 = " << result << std::endl;
    std::cout << std::endl;
  }

  return 0;
}