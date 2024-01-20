#pragma once

#include "parallelogram.h"

// Ромб
class Rhombus : public Parallelogram {
public:
  Rhombus(int a, int A, int B);

  // Все праметры для проверки исключении
  Rhombus(int a, int b, int с, int d, int A, int B, int C, int D);

  std::string get_name() override;

  std::string check() override;

};
