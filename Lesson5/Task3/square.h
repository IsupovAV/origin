#pragma once

#include "rectangle.h"

// Квадрат
class Square : public Rectangle {
public:
  explicit Square(int a);
  std::string get_name() override;
};
