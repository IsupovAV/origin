#pragma once

#include "parallelogram.h"

// Ромб
class Rhombus : public Parallelogram {
public:
  Rhombus(int a, int A, int B);
  std::string get_name() override;
};
