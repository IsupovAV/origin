#include <iostream>
#include <string>

class Figure {
public:
  Figure() : Figure(0) {
  }

  [[nodiscard]] int get_sides_count() const{
    return sides_count;
  }

  std::string get_name() {
    return name;
  }

protected:
  std::string name;
  explicit Figure(const int sides_count) : sides_count(sides_count), name("Фигура") {
  }

  private :
    int sides_count = 0;
};

constexpr int three_sides = 3;
constexpr int four_sides = 4;

class Triangle : public Figure{
public:
  Triangle() : Figure(three_sides) {
    name = "Треугольник";
  }
};

class Quadrangle : public Figure {
public:
  Quadrangle() : Figure(four_sides) {
    name = "Четырёхугольник";
  }
};

int main()
{
  Figure figure;
  Triangle triangle;
  Quadrangle quadrangle;
  std::cout << "Количество сторон:\n";
  std::cout << figure.get_name() << ": " << figure.get_sides_count()
            << std::endl;
  std::cout << triangle.get_name() << ": " << triangle.get_sides_count()
            << std::endl;
  std::cout << quadrangle.get_name() << ": " << quadrangle.get_sides_count()
            << std::endl;

  return 0;
}
