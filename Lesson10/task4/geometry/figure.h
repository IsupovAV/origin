#pragma once

#include <string>

constexpr int three_sides = 3;
constexpr int four_sides = 4;

#ifdef FIGURE_EXPORTS
#define FIGURE_API __declspec(dllexport)
#else
#define FIGURE_API __declspec(dllimport)
#endif

// Фигура
class Figure {
public:
  FIGURE_API Figure();

  FIGURE_API [[nodiscard]] int get_sides_count() const;

  FIGURE_API virtual std::string get_name();
  FIGURE_API virtual int get_side(char side);
  FIGURE_API virtual int get_angle(char angle);
  FIGURE_API virtual std::string dump_sides();
  FIGURE_API virtual std::string dump_angles();

protected:
  std::string name;
  FIGURE_API explicit Figure(int sides_count);

private:
  int sides_count = 0;
};
