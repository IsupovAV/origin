#include <catch2/catch_all.hpp>
#include <iostream>

int main(int argc, char *argv[]) {
#ifdef _WIN32
  system("chcp 65001");
#endif// _WIN32

  return Catch::Session().run(argc, argv);
}
