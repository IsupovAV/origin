#pragma once

#include <string>

constexpr int three_sides = 3;
constexpr int four_sides = 4;

// Фигура
class Figure {
public:
  Figure();

  [[nodiscard]] int get_sides_count() const;

  virtual std::string get_name();
  virtual int get_side(char side);
  virtual int get_angle(char angle);
  virtual std::string dump_sides();
  virtual std::string dump_angles();

protected:
  std::string name;
  explicit Figure(int sides_count);

private:
  int sides_count = 0;
};
