#include <fstream>

class Printable {
public:
  Printable(const std::string& text) : text_(text) {}
  virtual std::string print() const { return text_; }

private:
  std::string text_;
};

class DataHTML : public Printable {
public:
  DataHTML(const std::string& text) : Printable(text) {}
  std::string print() const override {
    return "<html>" + Printable::print() + "<html/>";
  }
};

class DataText : public Printable {
public:
  DataText(const std::string &text) : Printable(text) {}

  std::string print() const override { return Printable::print(); }
};

class DataJSON : public Printable {
public:
  DataJSON(const std::string &text) : Printable(text) {};
  std::string print() const override {
    return "{ \"data\": \"" + Printable::print() + "\"}";
  }
};

template <typename Type>
void saveTo(std::ofstream &file, Printable printable) {
  Type data(printable.print());
  file << data.print();
}

void saveToAsHTML(std::ofstream &file, const Printable &printable) {
  saveTo<DataHTML>(file, printable);
}

void saveToAsText(std::ofstream &file, const Printable &printable) {
  saveTo<DataText>(file, printable);
}

void saveToAsJSON(std::ofstream &file, const Printable &printable) {
  saveTo<DataJSON>(file, printable);
}

int main() {
  DataText data_text("text format");
  std::ofstream txt("file.txt");
  saveToAsText(txt, data_text);
  txt.close();

  DataHTML data_html("HTML format");
  std::ofstream html("file.html");
  saveToAsText(html, data_html);
  html.close();

  DataJSON data_json("JSON format");
  std::ofstream json("file.JSON");
  saveToAsJSON(json, data_json);
  json.close();

  return 0;
}