#include <catch2/catch_all.hpp>

#include "../src/simple_unique_ptr.h"

TEST_CASE("Тестирование упрощённой реализации simple_unique_ptr") {
  SECTION("1. Конструктор")
  {
    simple_unique_ptr<int> ptr1 { new int { 10 } };
    CHECK(*ptr1.get() == 10);

    simple_unique_ptr<std::string> ptr2 { new std::string { "hello world!" } };
    CHECK(*ptr2.get() == "hello world!");
  }

  SECTION("2. make_unique")
  {
    simple_unique_ptr<int> ptr1 { make_unique<int>(10) };
    CHECK(*ptr1.get() == 10);

    simple_unique_ptr<std::string> ptr2 { make_unique<std::string>("hello world!") };
    CHECK(*ptr2.get() == "hello world!");
  }

  SECTION("3. Текущий конструктор")
  {
    simple_unique_ptr<int> ptr1;
    CHECK(ptr1.get() == nullptr);

    simple_unique_ptr<std::string> ptr2 {};
    CHECK(ptr2.get() == nullptr);
  }

  SECTION("4. Конструктор")
  {
    simple_unique_ptr<int> ptr1 { new int { 10 } };
    CHECK(*ptr1 == 10);

    simple_unique_ptr<std::string> ptr2 { new std::string { "hello world!" } };
    CHECK(*ptr2 == "hello world!");

    simple_unique_ptr<std::vector<int>> ptr3 { new std::vector<int> { 1, 2, 3, 4, 5 } };
    CHECK((*ptr3)[1] == 2);
  }

  SECTION("5. Доступ по указателю")
  {
    simple_unique_ptr<std::string> ptr1 { new std::string { "hello world!" } };
    CHECK(ptr1->length() == 12);

    simple_unique_ptr<std::vector<int>> ptr3 { new std::vector<int> { 1, 2, 3, 4, 5 } };
    CHECK(!ptr3->empty());
  }

  SECTION("6. reset")
  {
    simple_unique_ptr<std::string> ptr { new std::string { "hello world!" } };
    CHECK(ptr->length() == 12);
    ptr.reset();
    CHECK(!ptr.get());
  }

  SECTION("7. Второй вариант reset ")
  {
    simple_unique_ptr<std::string> ptr { new std::string { "hello world!" } };
    ptr.reset(new std::string { "other owner!" });
    CHECK(*ptr == "other owner!");
  }

  SECTION("8. double ")
  {
    simple_unique_ptr<double> ptr { new double { 1.567 } };
    CHECK(*ptr == 1.567);
    if (ptr)
      ptr.reset();
    CHECK(!ptr);
  }

  SECTION("9. release ")
  {
    simple_unique_ptr<double> ptr { new double { 1.567 } };
    double* tmp;
    tmp = ptr.release();
    CHECK(*tmp == 1.567);
    CHECK(!ptr);  // освободил?
    delete tmp;
  }
}

int main(int argc, char *argv[]) {
#ifdef _WIN32
  system("chcp 65001");
#endif// _WIN32

  return Catch::Session().run(argc, argv);

}

