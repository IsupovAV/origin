#include "pch.h"
#include "rectangle.h"

Rectangle::Rectangle(int a, int b) : Parallelogram(a, b, 90, 90) {
  name = "Прямоугошльник";
}

std::string Rectangle::get_name()  { return name; }

