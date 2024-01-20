#include <iostream>

/*
 * Проверил два варианта
*/

// // создал свой класс исключение
// class BadLengthException
// {
// public:
//   explicit BadLengthException(const std::string&  message): message(message){}
//   [[nodiscard]] std::string get_message() const {return message;}
// private:
//   std::string message;
// };

constexpr int bad_length = -1;

size_t function(const std::string& str, const int forbidden_length) {
  const size_t result = str.length();
  if(result == forbidden_length) {
    throw bad_length;
    // throw BadLengthException{"Вы ввели слово запретной длины! До свидания"};
  }

  return result;
}

int main() {
  // тут проблема, если кодировка UTF-8 и str введена кирилицей, длина
  // будет кол-во символов * 2, если латиницей, то просто кол-во символов
  std::cout << "Введите запретную длину: ";
  int forbidden_length;
  std::cin >> forbidden_length;
  while (true) {
    std::cout << "Введите слово: ";
    std::string word;
    std::cin >> word;
    try {
      const size_t result = function(word, forbidden_length);
      std::cout << "Длина слова \"" << word <<"\" равна " << result << std::endl;
    }catch(const int& e) {
      //std::cout << e << std::endl;
      std::cout << "Вы ввели слово запретной длины! До свидания" << std::endl;
      // std::cout << ex.get_message() << std::endl;
      break;  // Выходим из цикла
    }
  }

  return 0;
}
