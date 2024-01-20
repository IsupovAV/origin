#pragma once

#include <string>
#include "geometric_exception.h"

constexpr int three_sides = 3;
constexpr int four_sides = 4;

// Фигура
class Figure {
public:

  Figure();

  int get_sides_count() const;

  virtual std::string get_name();
  virtual int get_side(char side);
  virtual int get_angle(char angle);
  virtual std::string dump_sides();
  virtual std::string dump_angles();
  virtual std::string dump_description();
  virtual std::string check();

protected:
  std::string name;
  explicit Figure(int sides_count);

private:
  int sides_count = 0;
};
