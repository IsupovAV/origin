#include "ini_parser.h"

namespace parser {

constexpr char LEFT_SECTION = '[';
constexpr char RIGHT_SECTION = ']';
constexpr char COMMENT = ';';
constexpr char EQUAL = '=';
constexpr char DOT = '.';

// удалить строки с комментариями
void ini_parser::trim_comment_(std::string &s) {
  auto pos = s.find(COMMENT);
  if (pos != std::string::npos)
    s = s.substr(0, pos);
}

ini_parser::ini_parser(const std::string &file_name) {
  std::ifstream file_(file_name);
  if (!file_.is_open())
    throw std::logic_error("can't open the file: " + file_name);

  int cnt_line = 0;
  std::string line;
  std::string name_section;
  while (std::getline(file_, line)) {
    ++cnt_line;
    ltrim(line);
    trim_comment_(line);
    if (line.empty()) {
      continue;
    }

    size_t pos = 0;
    size_t k = line.length();
    if (line[0] == LEFT_SECTION) {
      auto rhs = line.find_first_of(RIGHT_SECTION);
      if (rhs == std::string::npos) {
        throw std::invalid_argument("incorrect syntax not ], in line: " +
                                    std::to_string(cnt_line));
      }
      name_section = line.substr(1, k - 2);
      if (!content_.contains(name_section))
        content_[name_section] = std::map<std::string, std::string>{};
    } else if (line.find_first_of(RIGHT_SECTION) != std::string::npos) {
      throw std::invalid_argument("incorrect syntax not [, in line: " +
                                  std::to_string(cnt_line));
    } else if (pos = line.find_first_of(EQUAL), pos != std::string::npos) {
      std::string name_var = line.substr(0, pos);
      rtrim(name_var);
      std::string val = line.substr(pos + 1);
      trim(val);
      content_[name_section][name_var] = val;
    } else {
      ltrim(line);
      if (!line.empty())
        throw std::invalid_argument("incorrect syntax not =, in line: " +
                                    std::to_string(cnt_line));
    }
  }
}

void ini_parser::dump() const {
  for (const auto &[section, vars] : content_) {
    std::cout << '[' << section << "]\n";
    for (const auto &[var_name, val] : vars) {
      std::cout << var_name << "=";
      std::cout << val << std::endl;
    }
    std::cout << std::endl;
  }
}

std::pair<std::string, std::string>
ini_parser::unpack_(const std::string &sec_var) {
  if (sec_var.find(DOT) == std::string::npos)
    throw std::logic_error("bad request: missing dot character in the query");

  if (sec_var[0] == DOT)
    throw std::logic_error(
        "bad request: the dot character cannot come first in a query");

  auto pos = sec_var.find(DOT);
  std::string var = sec_var.substr(pos + 1, sec_var.length());
  std::string sec = sec_var.substr(0, pos);

  if (content_.contains(sec)) {
    if (content_[sec].contains(var)) {
      return {sec, var};
    } else {
      std::cout << "no variable: " << var << " in section: " << sec
                << std::endl;
      std::cout << "try the variables: " << std::endl;
      for (const auto &[key, val] : content_[sec])
        std::cout << key << std::endl;
    }
  } else {
    std::cout << "section: " << sec << " not found" << std::endl;
    std::cout << "try the section: " << std::endl;
    for (const auto &[section, val] : content_)
      std::cout << '[' << section << ']' << std::endl;
  }

  throw std::logic_error("bad request: section or variable is missing");
}

} // namespace parser
