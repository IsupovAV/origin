#include <iostream>
#include <string>

// Фигура
class Figure {
public:
  Figure() : Figure(0) {}

  [[nodiscard]] int get_sides_count() const { return sides_count; }

  virtual std::string get_name() { return name; }
  virtual std::string get_sides() { return ""; }
  virtual std::string get_angles() { return ""; }

protected:
  std::string name;
  Figure(int sides_count) : sides_count(sides_count), name("Фигура") {}

private:
  int sides_count = 0;
};

const int three_sides = 3;
const int four_sides = 4;

// Произвольный треугольник
class Triangle : public Figure {
public:
  Triangle(int a, int b, int c, int A, int B, int C)
      : Figure(three_sides), a_(a), b_(b), c_(c), A_(A), B_(B), C_(C) {
    name = "Треугольник";
  }

  int get_a() const { return a_; }
  int get_b() const { return b_; }
  int get_c() const { return c_; }

  int get_A() const { return A_; }
  int get_B() const { return B_; }
  int get_C() const { return C_; }

  std::string get_sides() override {
    return "a=" + std::to_string(a_) + " b=" + std::to_string(b_) +
           " c=" + std::to_string(c_);
  }

  std::string get_angles() override {
    return "A=" + std::to_string(A_) + " B=" + std::to_string(B_) +
           " C=" + std::to_string(C_);
  }

  std::string get_name() override { return name; }

private:
  int a_, b_, c_;
  int A_, B_, C_;
};

// Прямоугольный треугольник
class RightTriangl : public Triangle {
public:
  RightTriangl(int a, int b, int c, int A, int B)
      : Triangle(a, b, c, A, B, 90) {
    name = "Прямоугольный треугольник";
  }
  std::string get_name() override { return name; }
};

// Равнобедренный треугольник
class IsoscelesTriangle : public Triangle {
public:
  IsoscelesTriangle(int a, int b, int A, int B) : Triangle(a, b, a, A, B, A) {
    name = "Равнобедренный треугольник";
  }
  std::string get_name() override { return name; }
};

// Равносторонний треугольник
class EquilateralTriangle : public Triangle {
public:
  EquilateralTriangle(int a) : Triangle(a, a, a, 60, 60, 60) {
    name = "Равносторонний треугольник";
  }
  std::string get_name() override { return name; }
};

// Четырёхугольник
class Quadrangle : public Figure {
public:
  Quadrangle(int a, int b, int c, int d, int A, int B, int C, int D)
      : Figure(four_sides), a_(a), b_(b), c_(c), d_(d), A_(A), B_(B), C_(C),
        D_(D) {
    name = "Четырёхугольник";
  }

  int get_a() const { return a_; }
  int get_b() const { return b_; }
  int get_c() const { return c_; }
  int get_d() const { return d_; }

  int get_A() const { return A_; }
  int get_B() const { return B_; }
  int get_C() const { return C_; }
  int get_D() const { return D_; }

  std::string get_name() override { return name; }

  std::string get_sides() override {
    return "a=" + std::to_string(a_) + " b=" + std::to_string(b_) +
           " c=" + std::to_string(c_) + " d=" + std::to_string(d_);
  }

  std::string get_angles() override {
    return "A=" + std::to_string(A_) + " B=" + std::to_string(B_) +
           " C=" + std::to_string(C_) + " D=" + std::to_string(D_);
  }

private:
  int a_, b_, c_, d_;
  int A_, B_, C_, D_;
};

// Параллелограмм
class Parallelogram : public Quadrangle {
public:
  Parallelogram(int a, int b, int A, int B)
      : Quadrangle(a, b, a, b, A, B, A, B) {
    name = "Параллелограмм";
  }

  std::string get_name() override { return name; }
};

// Прямоугольник
class Rectangle : public Parallelogram {
public:
  Rectangle(int a, int b) : Parallelogram(a, b, 90, 90) {
    name = "Прямоугошльник";
  }

  std::string get_name() override { return name; }
};

// Ромб
class Rhombus : public Parallelogram {
public:
  Rhombus(int a, int A, int B) : Parallelogram(a, a, A, B) { name = "Ромб"; }

  std::string get_name() override { return name; }
};

// Квадрат
class Square : public Rectangle {
public:
  Square(int a) : Rectangle(a, a) { name = "Квадрат"; }

  std::string get_name() override { return name; }
};

void print_info(Figure &fig) {
  std::cout << fig.get_name() << ":\n";
  std::cout << "Стороны: " << fig.get_sides() << "\n";
  std::cout << "Углы: " << fig.get_angles() << "\n";
  std::cout << std::endl;
}

int main() {
  Triangle triangle(10, 20, 30, 50, 60, 70); // произвольный треугольник
  RightTriangl right_triangle(10, 20, 30, 50, 60); // прямоугольный треугольник
  IsoscelesTriangle isosceles_triangle(10, 20, 50, 60); // равнобедренный треугольник
  EquilateralTriangle equilateral_triangle(30); // равностороний треугольник

  Quadrangle quadrangle(10, 20, 30, 40, 50, 60, 70, 80); // произвольный четырехуголььник
  Rectangle rect(10, 20);                      // прямоугольник
  Square square(20);                           // квадрат
  Parallelogram parallelogram(20, 30, 30, 40); // параллелограмм
  Rhombus rhombus(30, 30, 40);                 // ромб

  print_info(triangle);
  print_info(right_triangle);
  print_info(isosceles_triangle);
  print_info(equilateral_triangle);

  print_info(quadrangle);
  print_info(rect);
  print_info(square);
  print_info(parallelogram);
  print_info(rhombus);

  return 0;
}
