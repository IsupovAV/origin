#include <iostream>
#include <string>

#include "right_triangle.h"
#include "isosceles_triangle.h"
#include "equilateral_triangle.h"
#include "rhombus.h"
#include "rectangle.h"
#include "square.h"

int main() {
  try {
    Triangle triangle(10, 20, 30, 70, 60, 50); // произвольный треугольник
    std::cout << triangle.dump_description() << "создан" << std::endl;
  }catch (const GeometricException& m) {
    std::cout << "Ошибка создания фигуры. Причина: " << m.what() << std::endl;
  }

  try {
    RightTriangle right_triangle(10, 20, 30, 50, 40, 90); // прямоугольный треугольник
    std::cout << right_triangle.dump_description() << "создан" << std::endl;
  }catch(const GeometricException& m) {
    std::cout << "Ошибка создания фигуры. Причина: " << m.what() << std::endl;
  }

  try {
    IsoscelesTriangle isosceles_triangle(10, 20, 50, 80); // равнобедренный треугольник
    std::cout << isosceles_triangle.dump_description() << "создан" << std::endl;
  }catch(const GeometricException& m) {
    std::cout << "Ошибка создания фигуры. Причина: " << m.what() << std::endl;
  }

  try {
    EquilateralTriangle equilateral_triangle(30, 30, 40, 60, 60, 60); // равностороний треугольник
    std::cout << equilateral_triangle.dump_description() << "создан" << std::endl;
  }catch(const GeometricException& m) {
    std::cout << "Ошибка создания фигуры. Причина: " << m.what() << std::endl;
  }

  try {
    EquilateralTriangle equilateral_triangle(50); // равностороний треугольник
    std::cout << equilateral_triangle.dump_description() << "создан" << std::endl;
  }catch(const GeometricException& m) {
    std::cout << "Ошибка создания фигуры. Причина: " << m.what() << std::endl;
  }

  try {
    Quadrangle quadrangle(10, 20, 30, 40, 50, 60, 70, 80); // произвольный четырехуголььник
    std::cout << quadrangle.dump_description() << "создан" << std::endl;
  }catch(const GeometricException& m) {
    std::cout << "Ошибка создания фигуры. Причина: " << m.what() << std::endl;
  }

  try {
    Rectangle rect(10, 20, 10, 20, 90, 90, 90, 90); // прямоугольник полный конструктор
    std::cout << rect.dump_description() << "создан" << std::endl;
  }catch(const GeometricException& m) {
    std::cout << "Ошибка создания фигуры. Причина: " << m.what() << std::endl;
  }

  try {
    Square square(20); // квадрат
    std::cout << square.dump_description() << "создан" << std::endl;
  }catch(const GeometricException& m) {
    std::cout << "Ошибка создания фигуры. Причина: " << m.what() << std::endl;
  }

  try {
    Rhombus rhombus(30, 40, 30, 40, 140, 40, 140, 40); // ромб
    std::cout << rhombus.dump_description() << "создан" << std::endl;
  }catch(const GeometricException& m) {
    std::cout << "Ошибка создания фигуры. Причина: " << m.what() << std::endl;
  }

  try {
    Parallelogram parallelogram(20, 30, 20, 30, 60, 120, 60, 120); // параллелограмм
    std::cout << parallelogram.dump_description() << "создан" << std::endl;
  }catch(const GeometricException& m) {
    std::cout << "Ошибка создания фигуры. Причина: " << m.what() << std::endl;
  }

  try {
    Figure *fig;
    IsoscelesTriangle isosceles_triangle(10, 20, 50, 80); // равнобедренный треугольник
    fig = &isosceles_triangle;
    std::cout << fig->dump_description() << "создан" << std::endl;
  }catch(const GeometricException& m) {
    std::cout << "Ошибка создания фигуры. Причина: " << m.what() << std::endl;
  }

  return 0;
}
