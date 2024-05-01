#pragma once

#include <algorithm>
#include <any>
#include <cctype>
#include <fstream>
#include <iostream>
#include <map>
#include <memory>
#include <string>

namespace parser {

constexpr char LEFT_SECTION = '[';
constexpr char RIGHT_SECTION = ']';
constexpr char COMMENT = ';';
constexpr char EQUAL = '=';
constexpr char DOT = '.';

// https://stackoverflow.com/questions/216823/how-to-trim-a-stdstring
// trim from start (in place)
inline void ltrim(std::string &s) {
  s.erase(s.begin(), std::find_if(s.begin(), s.end(),
    [](auto ch) {
            return !std::isspace(ch);
          }));
}

// trim from end (in place)
inline void rtrim(std::string &s) {
  s.erase(std::find_if(s.rbegin(), s.rend(),
  [](auto ch) { return !std::isspace(ch); })
              .base(),
          s.end());
}

inline void trim(std::string &s) {
  ltrim(s);
  rtrim(s);
}

class ini_parser {
public:

  ini_parser(const std::string& file_name);
  ~ini_parser() = default;

  template <typename T>
  T get_value(std::string &&request) {
    if (request.find(DOT) == std::string::npos)
      throw std::logic_error("bad request");

    if (request[0] == DOT)
      throw std::logic_error("bad request");

    std::string var_name =
        request.substr((request.find(DOT) + 1), request.length());
    request.erase(request.find(DOT), request.length());

    if(content_.contains(request)){
      if (content_[request].contains(var_name)) {
        return any_cast<T>(content_[request][var_name]);
      } else{
        std::cout << "no variable: " << var_name << " in section: "
                  << request << std::endl;
        std::cout << "try the variables: " << std::endl;
        for(const auto& [key, val] : content_[request])
          std::cout << key << std::endl;
      }
    }else{
      std::cout << "section: " << request << " not found" << std::endl;
      std::cout << "try the section: " << std::endl;
      for(const auto& [section, val] : content_)
        std::cout << '[' << section << ']' << std::endl;
    }

    throw std::logic_error("bad request");
  }

  void dump() const;

private:
  void trim_comment_(std::string& s);
  std::any convert_value_(std::string& val);

  std::map<std::string, std::map<std::string, std::any>> content_;
};
} // namespace parser
