#pragma once

#include "quadrangle.h"

// Параллелограмм
class Parallelogram : public Quadrangle {
public:
  Parallelogram(int a, int b, int A, int B);
  std::string get_name() override;
};
