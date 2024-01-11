#include "figure.h"

Figure:: Figure(const int sides_count) : name("Фигура"), sides_count(sides_count) {
}

Figure::Figure(): Figure(0) {
}

int Figure::get_sides_count() const {
  return sides_count;
}

std::string Figure::get_name() { return name; }

std::string Figure::dump_sides() { return ""; }

std::string Figure::dump_angles() { return ""; }

int Figure::get_side(char side) { return 0; }

int Figure::get_angle(char angle) { return 0; }
