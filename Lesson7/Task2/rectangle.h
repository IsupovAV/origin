#pragma once

#include "parallelogram.h"

// Прямоугольник
class Rectangle : public Parallelogram {
public:
  Rectangle(int a, int b);

  // Полный конструктор для проверки работы исключений
  Rectangle(int a, int b, int с, int d, int A, int B, int C, int D);

  std::string get_name() override;

  std::string check() override;

};
