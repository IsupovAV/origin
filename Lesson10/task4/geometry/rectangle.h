#pragma once

#include "parallelogram.h"

#ifdef RECTANGLE_EXPORTS
#define RECTANGLE_API __declspec(dllexport)
#else
#define RECTANGLE_API __declspec(dllimport)
#endif

// Прямоугольник
class RECTANGLE_API Rectangle : public Parallelogram {
public:
  Rectangle(int a, int b);
  std::string get_name() override;
};
