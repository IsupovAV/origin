#pragma once

#include "parallelogram.h"

// Прямоугольник
class Rectangle : public Parallelogram {
public:
  Rectangle(int a, int b);
  std::string get_name() override;
};
