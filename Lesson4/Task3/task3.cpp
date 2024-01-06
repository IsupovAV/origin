#include <iostream>
#include <string>

// Фигура
class Figure {
public:
  Figure() : Figure(0) {}

  int get_sides_count() const { return sides_count; }

  virtual bool check() {
    return true;
  }

  virtual void print_info() {
    std::cout << get_name() << ":\n";
    std::cout << (check() ? "Правильная": "Неправильная") << '\n';
    std::cout << "Количество сторон: " << get_sides_count() << '\n';
  }

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

  bool check() override{
    return A_ + B_ + C_ == 180 && get_sides_count() == 3;
  }

  std::string get_sides() override {
    return "a=" + std::to_string(a_) + " b=" + std::to_string(b_) +
           " c=" + std::to_string(c_);
  }

  std::string get_angles() override {
    return "A=" + std::to_string(A_) + " B=" + std::to_string(B_) +
           " C=" + std::to_string(C_);
  }

  std::string get_name() override { return name; }

  void print_info() override {
    Figure::print_info();
    std::cout << "Стороны: " << get_sides() << '\n';
    std::cout << "Углы: " << get_angles() << '\n';
    std::cout << std::endl;
  }

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

  bool check() override {
    return Triangle::check() && get_C() == 90;
  }

  std::string get_name() override { return name; }
};

// Равнобедренный треугольник
class IsoscelesTriangle : public Triangle {
public:
  IsoscelesTriangle(int a, int b, int A, int B) : Triangle(a, b, a, A, B, A) {
    name = "Равнобедренный треугольник";
  }

  bool check() override {
    return Triangle::check() && get_a() == get_c() && get_A() == get_C();
  }

  std::string get_name() override { return name; }
};

// Равносторонний треугольник
class EquilateralTriangle : public Triangle {
public:
  EquilateralTriangle(int a) : Triangle(a, a, a, 60, 60, 60) {
    name = "Равносторонний треугольник";
  }

  bool check() override {
    return Triangle::check() && get_a() == get_b() && get_b()  == get_c() &&
           get_A() == 60 && get_B() == 60 && get_C() == 60;
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

  bool check() override {
    return A_ + B_ + C_ + D_ == 360 && get_sides_count() == 4;
  }

  void print_info() override {
    Figure::print_info();
    std::cout << "Стороны: " << get_sides() << '\n';
    std::cout << "Углы: " << get_angles() << '\n';
    std::cout << std::endl;
  }

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

  bool check() override {
    return Quadrangle::check() && get_a() == get_c() && get_b() == get_d() &&
           get_A() == get_C() && get_B() == get_D();
  }

  std::string get_name() override { return name; }
};

// Прямоугольник
class Rectangle : public Parallelogram {
public:
  Rectangle(int a, int b) : Parallelogram(a, b, 90, 90) {
    name = "Прямоугошльник";
  }

  bool check() override {
    return Parallelogram::check() &&
           get_A() == 90 && get_B() == 90;
  }

  std::string get_name() override { return name; }
};

// Ромб
class Rhombus : public Parallelogram {
public:
  Rhombus(int a, int A, int B) : Parallelogram(a, a, A, B) { name = "Ромб"; }
  bool check() override {
    return Parallelogram::check() && get_A() == get_B() && get_a() == get_b();
  }

  std::string get_name() override { return name; }
};

// Квадрат
class Square : public Rectangle {
public:
  Square(int a) : Rectangle(a, a) { name = "Квадрат"; }

  bool check() override {
    return Rectangle::check() && get_a() == get_b();
  }

  std::string get_name() override { return name; }
};

int main() {
  Figure figure;
  figure.print_info();
  std::cout << std::endl;

  Triangle triangle(10, 20, 30, 50, 60, 70); // произвольный треугольник
  triangle.print_info();

  RightTriangl right_triangle(10, 20, 30, 50, 60); // прямоугольный треугольник
  right_triangle.print_info();

  RightTriangl right_triangle1(10, 20, 30, 50, 40); // ещё прямоугольный треугольник
  right_triangle1.print_info();

  IsoscelesTriangle isosceles_triangle(10, 20, 50, 60); // равнобедренный треугольник
  isosceles_triangle.print_info();

  EquilateralTriangle equilateral_triangle(30); // равностороний треугольник
  equilateral_triangle.print_info();


  Quadrangle quadrangle(10, 20, 30, 40, 50, 60, 70, 80); // произвольный четырехуголььник
  quadrangle.print_info();

  Rectangle rect(10, 20);                      // прямоугольник
  rect.print_info();

  Square square(20);                           // квадрат
  square.print_info();

  Parallelogram parallelogram(20, 30, 30, 40); // параллелограмм
  parallelogram.print_info();

  Rhombus rhombus(30, 30, 40);                 // ромб
  rhombus.print_info();

  return 0;
}
