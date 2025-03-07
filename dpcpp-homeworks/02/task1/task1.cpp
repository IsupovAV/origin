#include <algorithm>
#include <iostream>
#include <string>

class Text {
public:
  virtual void render(const std::string& row) const { std::cout << row; }
};

class Decorator : public Text {
public:
  explicit Decorator(Text *text) : text_(text) {};
  Text *text_;
};

class Italic : public Decorator {
public:
  explicit Italic(Text *text) : Decorator(text) {};
  void render(const std::string &row) const override {
    std::cout << "<i>";
    text_->render(row);
    std::cout << "</i>";
  }
};

class Bold : public Decorator {
public:
  explicit Bold(Text *text) : Decorator(text) {}
  void render(const std::string &row) const override {
    std::cout << "<b>";
    text_->render(row);
    std::cout << "</b>";
  }
};

class Paragraph : public Decorator {
public:
  explicit Paragraph(Text *text) : Decorator(text) {}
  void render(const std::string &row) const override {
    std::cout << "<p>";
    text_->render(row);
    std::cout << "</p>";
  }
};

class Reversed : public Decorator {
public:
  explicit Reversed(Text *text) : Decorator(text) {}
  void render(const std::string& row) {
    auto tmp_ = row;
    std::reverse(tmp_.begin(), tmp_.end());
    std::cout << tmp_;
  }
};

class Link : public Decorator {
public:
  explicit Link(Text *text) : Decorator(text) {}
  void render(const std::string &site, const std::string &row){
    auto tmp = "<a href=" + site + ">" + row + "/a";
    text_->render(tmp);
  }
};

static void test_decorator() {
  {
    auto simple_text = new Text();
    simple_text->render("Simple text");
    std::cout << std::endl;

    Italic *it_text = new Italic(simple_text);
    it_text->render("Italice text");
    std::cout << std::endl;

    Bold *b_text = new Bold(simple_text);
    it_text->render("Bold text");
    std::cout << std::endl;

    auto block_text = new Bold(new Italic(new Text()));
    block_text->render("Block text with Bold and Itelic");
    std::cout << std::endl;
  }

  {
    auto text_block = new Paragraph(new Text());
    text_block->render("Paragraph text");
    std::cout << std::endl;
  }

  {
    auto text_block = new Reversed(new Text());
    text_block->render("Reversed text >- txet desreveR");
    std::cout << std::endl;
  }

  {
    auto text_block = new Link(new Text());
    text_block->render("netology.ru", "Link text");
    std::cout << std::endl;
  }
}

int main() {
  test_decorator();

  return 0;
}