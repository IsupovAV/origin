#pragma once

#include "rectangle.h"

// Квадрат
class Square : public Rectangle {
public:
  explicit Square(int a);

  // Полный конструктор для проверки работы исключений
  explicit Square(int a, int b, int c, int d, int A, int B, int C, int D);

  std::string get_name() override;

  std::string check() override;

};
