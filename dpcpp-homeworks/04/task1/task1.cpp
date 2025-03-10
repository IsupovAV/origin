#include <fstream>

class Printable {
 // Принцип разделения интерфейса (interface segregation principle)
 // «много интерфейсов, специально предназначенных для клиентов, лучше,
 // чем один интерфейс общего назначения» (ISP)
 // Printable не является узкоспецализированным.
public:
  virtual ~Printable() = default;
  virtual std::string printAsHTML() const = 0;
  virtual std::string printAsText() const = 0;
  virtual std::string printAsJSON() const = 0;
};

class Data : public Printable {
// Принцип открытости / закрытости(open - closed principle) "программные сущности … 
// должны быть открыты для расширения, но закрыты для модификации". (OCP)
// При добавлении нового формата необходимо вносить изменения и в базовый класс, и в наследник.

// Принцип подстановки Лисков (Liskov substitution principle) "функции,
// которые используют базовый тип, должны иметь возможность использовать подтипы 
// базового типа не зная об этом". printAsHTML(), printAsText(), printAsJSON() с экземпляром 
// Data приведет к исключению.

public:
  enum class Format { kText, kHTML, kJSON };

  Data(std::string data, Format format)
      : data_(std::move(data)), format_(format) {}

  std::string printAsHTML() const override {
    if (format_ != Format::kHTML) {
      throw std::runtime_error("Invalid format!");
    }
    return "<html>" + data_ + "<html/>";
  }
  std::string printAsText() const override {
    if (format_ != Format::kText) {
      throw std::runtime_error("Invalid format!");
    }
    return data_;
  }
  std::string printAsJSON() const override {
    if (format_ != Format::kJSON) {
      throw std::runtime_error("Invalid format!");
    }
    return "{ \"data\": \"" + data_ + "\"}";
  }

private:
  std::string data_;
  Format format_;
};

void saveTo(std::ofstream &file, const Printable &printable,
            Data::Format format) {
  switch (format) {
  case Data::Format::kText:
    file << printable.printAsText();
    break;
  case Data::Format::kJSON:
    file << printable.printAsJSON();
    break;
  case Data::Format::kHTML:
    file << printable.printAsHTML();
    break;
  }
}

void saveToAsHTML(std::ofstream &file, const Printable &printable) {
  saveTo(file, printable, Data::Format::kHTML);
}

void saveToAsJSON(std::ofstream &file, const Printable &printable) {
  saveTo(file, printable, Data::Format::kJSON);
}

void saveToAsText(std::ofstream &file, const Printable &printable) {
  saveTo(file, printable, Data::Format::kText);
}