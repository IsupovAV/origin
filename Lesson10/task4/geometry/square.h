#pragma once

#include "rectangle.h"

#ifdef SQUARE_EXPORTS
#define SQUARE_API __declspec(dllexport)
#else
#define SQUARE_API __declspec(dllimport)
#endif

// Квадрат
class SQUARE_API Square : public Rectangle {
public:
  explicit Square(int a);
  std::string get_name() override;
};
