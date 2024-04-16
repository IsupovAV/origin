#include <iomanip>
#include <iostream>
#include <memory>
#include <vector>

class tridiagonal_matrix {
public:
  std::vector<double> m_down;
  std::vector<double> m_upper;
  std::vector<double> m_middle;
  tridiagonal_matrix(
      const std::vector<double> &down,
      const std::vector<double> &upper,
      const std::vector<double> &middle) : m_down{down}, m_upper{upper}, m_middle{middle} {};
  ~tridiagonal_matrix() { std::cout << "destructor called\n"; }

  std::unique_ptr<tridiagonal_matrix>clone(){
    return std::make_unique<tridiagonal_matrix>(m_down, m_upper, m_middle);
  }
};

std::ostream& operator<< (std::ostream& os, const std::vector<double>& v){
  // сделал красивенькую печать
  os << std::fixed << std::setprecision(2);
  for(const auto& e: v){
    os << std::setw(5) << e << ' ';
  }
  return os;
}

std::ostream& operator<<(std::ostream& os, const tridiagonal_matrix* matrix){
  os << "down:\t";
  os << matrix->m_down << std::endl;
  os << "upper:\t";
  os << matrix->m_upper << std::endl;
  os << "middle:\t";
  os << matrix->m_middle << std::endl;

  return os;
}

int main() {
#ifdef _WIN32
  system("chcp 65001");
#endif// _WIN32

  auto down = std::vector<double>{-4.01, 5.0, -3.56};
  auto upper = std::vector<double>{14.0, 8.0, 0.19};
  auto middle = std::vector<double>{3.0, 1.0, 7.0, 100.25};
  auto matrix = std::make_unique<tridiagonal_matrix>(
      down,
      upper,
      middle);
  std::cout << matrix;
  std::cout << std::endl;

  std::cout << "склонировал:\n";
  auto matrix_clone = matrix->clone();
  std::cout << matrix_clone;
  std::cout << std::endl;

  return 0;
}