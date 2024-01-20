#pragma once

#include "quadrangle.h"

// Параллелограмм
class Parallelogram : public Quadrangle {
public:
  Parallelogram(int a, int b, int A, int B);

  // Полный конструктор для проверки работы исключений
  Parallelogram(int a, int b, int с, int d, int A, int B, int C, int D);

  std::string get_name() override;

  std::string check() override;

};
