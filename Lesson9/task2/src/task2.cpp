#include <iostream>
#include <string>

#include "right_triangle.h"
#include "isosceles_triangle.h"
#include "equilateral_triangle.h"
#include "rhombus.h"
#include "rectangle.h"
#include "square.h"

// Вспомогательная функция для печати, в формате примера из задачи
void print_info(Figure&fig) {
  std::cout << fig.get_name() << ":\n";
  std::cout << "Стороны: " << fig.dump_sides() << "\n";
  std::cout << "Углы: " << fig.dump_angles() << "\n";
  std::cout << std::endl;
}

int main() {
  Triangle triangle(10, 20, 30, 50, 60, 70); // произвольный треугольник
  RightTriangle right_triangle(10, 20, 30, 50, 60); // прямоугольный треугольник
  IsoscelesTriangle isosceles_triangle(10, 20, 50, 60); // равнобедренный треугольник
  EquilateralTriangle equilateral_triangle(30); // равностороний треугольник

  Quadrangle quadrangle(10, 20, 30, 40, 50, 60, 70, 80); // произвольный четырехуголььник
  Rectangle rect(10, 20); // прямоугольник
  Square square(20); // квадрат
  Parallelogram parallelogram(20, 30, 30, 40); // параллелограмм
  Rhombus rhombus(30, 30, 40); // ромб

  print_info(triangle);
  print_info(right_triangle);
  print_info(isosceles_triangle);
  print_info(equilateral_triangle);

  print_info(quadrangle);
  print_info(rect);
  print_info(square);
  print_info(parallelogram);
  print_info(rhombus);

  Figure *fig;
  fig = &right_triangle;
  std::cout << "Сторона c: " << fig->get_side('c') << " Угол C: " << fig->get_angle('C') << std::endl;

  fig = &parallelogram;
  std::cout << "Сторона a: " << fig->get_side('c') << " Угол B: " << fig->get_angle('B') << std::endl;


  return 0;
}
