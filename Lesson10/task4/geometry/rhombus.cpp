#include "pch.h"
#include "rhombus.h"

Rhombus::Rhombus(int a, int A, int B) : Parallelogram(a, a, A, B) { name = "Ромб"; }

std::string Rhombus::get_name()  { return name; }
