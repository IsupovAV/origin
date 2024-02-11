#include "simulator/simulator.h"
#include <iostream>

int main() {
#ifdef _WIN32
  system("chcp 65001");
#endif // _WIN32
  std::cout << "Добро пожаловать в гоночный симулятор!" << std::endl;
  race::Simulator sml;
  
	while (sml.ExecuteSimulation());

  return 0;
}
