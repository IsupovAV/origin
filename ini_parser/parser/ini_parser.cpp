#include "ini_parser.h"

namespace parser {

// удалить строки с комментариями
void ini_parser::trim_comment_(std::string& s){
  auto pos = s.find(COMMENT);
  if(pos != std::string::npos)
    s = s.substr(0, pos);
}

// преобразовать строку в допустимые значения: int, double, string
std::any ini_parser::convert_value_(std::string& val){
  if(val.find_first_of(DOT) != std::string::npos && atof(val.c_str())){
    return atof(val.c_str());
  }else if(atoi(val.c_str())){
    return atoi(val.c_str());
  }

  return val;
}

ini_parser::ini_parser(const std::string& file_name){
  std::ifstream  file_(file_name);
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

    int pos = 0;
    int k = line.length();
    if (line[0] == LEFT_SECTION) {
      auto rhs = line.find_first_of(RIGHT_SECTION);
      if (rhs == std::string::npos) {
        throw std::invalid_argument("incorrect syntax not ], in line: " +
                                    std::to_string(cnt_line));
      }
      name_section = line.substr(1, k - 2);
      if(!content_.contains(name_section))
        content_[name_section] = std::map<std::string, std::any>{};
    }else if(line.find_first_of(RIGHT_SECTION) != std::string::npos){
      throw std::invalid_argument("incorrect syntax not [, in line: " +
                                  std::to_string(cnt_line));
    }else if(pos = line.find_first_of(EQUAL), pos != std::string::npos){
      std::string name_var = line.substr(0, pos);
      rtrim(name_var);
      std::string val = line.substr(pos + 1);
      trim(val);
      content_[name_section][name_var] = convert_value_(val);
    }else {
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

      if (val.type() == typeid(int)) {
        std::cout << std::any_cast<int>(val) << std::endl;
      } else if (val.type() == typeid(double)) {
        std::cout << std::any_cast<double>(val) << std::endl;
      } else {
        std::cout << std::any_cast<std::string>(val) << std::endl;
      }
    }
    std::cout << std::endl;
  }
}

} // namespace parser
