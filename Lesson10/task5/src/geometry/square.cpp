#include "square.h"

Square::Square(const int a) : Rectangle(a, a) { name = "Квадрат"; }

std::string Square::get_name()  { return name; }

