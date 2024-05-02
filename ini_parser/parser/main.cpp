#include "ini_parser.h"

using namespace parser;

int main(int argc, char **argv) {
#ifdef _WIN32
  system("chcp 65001");
  setlocale(LC_ALL, ".UTF8");
#endif // _WIN32

  std::string fname = "config.ini";
  ini_parser parser(fname);
  std::cout << "Dump " << fname << std::endl;
  parser.dump();
  std::cout << std::endl;

  std::cout << "Запросы к " << fname << std::endl;
  try {
    auto value = parser.get_value<int>("Section.Var");
    std::cout << value << std::endl;
  } catch (std::exception &ex) {
    std::cout << ex.what() << std::endl;
  }
  std::cout << std::endl;

  try {
    auto value = parser.get_value<double>("Section1.var3");
    std::cout << value << std::endl;
  } catch (std::exception &ex) {
    std::cout << ex.what() << std::endl;
  }
  std::cout << std::endl;

  try {
    auto value = parser.get_value<double>("Section4.var1");
    std::cout << value << std::endl;
  } catch (std::exception &ex) {
    std::cout << ex.what() << std::endl;
  }
  std::cout << std::endl;

  return 0;
}
