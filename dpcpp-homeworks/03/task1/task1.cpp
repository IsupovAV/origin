// task1.cpp : Задание 1. Паттерн «Команда»
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

// Вспомогательная функция печати содержимого log файла
static void print_file(const std::string &file_path) {
  std::ifstream in(file_path);
  if (!in.is_open()) {
    std::cerr << "file not open: " << file_path << std::endl;
    return;
  }

  std::cout << "\nprint the contents of \'" << file_path << "\'" << std::endl;
  std::string s;
  while (std::getline(in, s)) {
    std::cout << s << std::endl;
  }
}

class LogCommand {
public:
  virtual ~LogCommand() = default;
  virtual void print(const std::string &message) noexcept = 0;
};

class LogToConsoleCommand : public LogCommand {
public:
  void print(const std::string &message) noexcept override {
    std::cout << message << std::endl;
  };
};

class LogToFileCommand : public LogCommand {
public:
  explicit LogToFileCommand(const std::string &log_path) {
    out_.open(log_path, std::ios::out);
    if (!out_.is_open()) {
      std::cerr << "file not open: " << log_path << std::endl;
      exit(-1);
    }
  }
  ~LogToFileCommand() { out_.close(); };

  void print(const std::string &message) noexcept override {
    out_ << message << std::endl;
  };

private:
  std::ofstream out_;
};

static void print(LogCommand &command, const std::string &message) {
  command.print(message);
}

int main() {
  const std::string file_path = "output.txt";
  LogToConsoleCommand to_console;
  LogToFileCommand to_file{file_path};

  print(to_console, "write to console log");
  print(to_file, "write to file log");
  print(to_file, "write to file log again");

  print_file(file_path);

  return 0;
}