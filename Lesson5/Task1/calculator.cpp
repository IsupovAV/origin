#include <cmath>  // подключил для pow

#include "calculator.h"

double add(const double left, const double right) { return left + right; }

double sub(const double left, const double right) { return left - right; }

double mul(const double left, const double right) { return left * right; }

double division(const double left, const double right) {
  if (right != 0)
    return left / right;
  return NAN; // если делитель ноль
}

double power(const double left, const double right) {
  return pow(left, right);
}
