#include "ini_parser.h"

int main(int argc, char **argv) {
#ifdef _WIN32
  system("chcp 65001");
  setlocale(LC_ALL, ".UTF8");
#endif // _WIN32

  std::string fname = "config.ini";
  parser::ini_parser parser(fname);
  std::cout << "Dump " << fname << std::endl;
  parser.dump();
  std::cout << std::endl;

  std::cout << "Запросы к " << fname << std::endl;
  try {
    std::cout << "int: Section1.var1 = "
              << parser.get_value<int>("Section1.var1") << std::endl;
    std::cout << "double: Section1.var1 = "
              << parser.get_value<double>("Section1.var1") << std::endl;
    std::cout << "string: Section1.var1 = "
              << parser.get_value<std::string>("Section1.var1") << std::endl;
  } catch (std::exception &ex) {
    std::cout << ex.what() << std::endl;
  }
  std::cout << std::endl;

  try {
    auto value = parser.get_value<int>("Section1.var8");
    std::cout << value << std::endl;
  } catch (std::exception &ex) {
    std::cout << ex.what() << std::endl;
  }
  std::cout << std::endl;

  try {
    auto value = parser.get_value<int>("Section.Var");
    std::cout << value << std::endl;
  } catch (std::exception &ex) {
    std::cout << ex.what() << std::endl;
  }
  std::cout << std::endl;

  try {
    auto value = parser.get_value<double>("Section1.var3");
    std::cout << "Section1.var3 = " << value << std::endl;
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

  try {
    std::cout << "string: Section4.Mode = "
              << parser.get_value<std::string>("Section4.Mode") << std::endl;
    std::cout << "int: Section4.Mode = "
              << parser.get_value<int>("Section4.Mode") << std::endl;
  } catch (std::exception &ex) {
    std::cout << ex.what() << std::endl;
  }
  std::cout << std::endl;

  return 0;
}
