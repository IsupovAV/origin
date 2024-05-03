#pragma once

#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <map>
#include <memory>
#include <string>

#include "string_utils.h"

namespace parser {

class ini_parser {
public:
  ini_parser(const std::string &file_name);
  ~ini_parser() = default;

  // 1. Основной шаблон, по которому будет проводиться сопоставление
  template <typename T>
  T get_value(
      const std::string &section_var) { // вместо тела, можно поставить ;
                                        // будет просто ошибка компиляции
    // Тут только одно предупреждение, чтобы сказать, что надо пользоваться уже
    // заданными конвертациями
    static_assert(sizeof(T) == -1, "not implemented type for get_value");
  }

  // 2. конкретный шаблон для стринга
  template <> 
  std::string get_value(const std::string &section_var) {
    auto p = unpack_(section_var); // p.first - section, p.second - var
    return get_value_string_(p.first, p.second);
  }

  // 3. конкретный шаблон для инта
  template <> 
  int get_value(const std::string &section_var) {
    auto p = unpack_(section_var); // p.first - section, p.second - var
    auto str_val = get_value_string_(p.first, p.second);
    if (!atof(str_val.c_str()))
      throw std::logic_error(
          "bad request, variable " + p.second + " cannot be converted to type int");

    return atoi(str_val.c_str());
  }

  // 4. конкретный шаблон для float/double
  template <> 
  double get_value(const std::string &section_var) {
    auto p = unpack_(section_var); // p.first - section, p.second - var
    auto str_val = get_value_string_(p.first, p.second);
    if (!atof(str_val.c_str()))
      throw std::logic_error("bad request, variable " + p.second +
                             " cannot be converted to type double");

    return atof(str_val.c_str());
  }

  void dump() const;

private:
  void trim_comment_(std::string &s);
  std::string get_value_string_(const std::string &section,
                                const std::string &var) {
    return content_[section][var];
  }

  // распаковка section.var в пару {section, var}
  std::pair<std::string, std::string> unpack_(const std::string &sec_var);

  // убрал any
  std::map<std::string, std::map<std::string, std::string>> content_;
};

} // namespace parser
