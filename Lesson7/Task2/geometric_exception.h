#pragma once

#include <stdexcept>
#include <utility>

class GeometricException final: public std::domain_error{
public:
  explicit GeometricException(const std::string& what_arg): domain_error(what_arg) {
  }

  ~GeometricException() override {}

};
