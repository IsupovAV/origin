#include <catch2/catch_all.hpp>

#include "simple_vector.h"

TEST_CASE("Тестирование упрощённой реализации шаблона вектора simple_vector") {

  SECTION("1. at(int index)") {
    simple_vector<int> v(3);
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    CHECK(v.at(2) == 3);
    REQUIRE_THROWS_AS(v.at(3), std::runtime_error);
  }

  SECTION("2. push_back(T value)") {
    simple_vector<double> v(3);
    v.push_back(1.0);
    v.push_back(2.5);
    v.push_back(3.7);
    CHECK(int(v.at(0)) == 1);
    CHECK(v.at(2) == 3.7);
  }

  SECTION("3. size() && capacity()") {
    simple_vector<int> v(3);
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    CHECK(v.size() == 3);
    CHECK(v.capacity() == 3);
    v.push_back(4);
    v.push_back(5);
    CHECK(v.size() == 5);
    CHECK(v.capacity() == 6);
  }

  SECTION("4. operator = ") {
    simple_vector<std::string> v(4);
    v.push_back("name1");
    v.push_back("name2");
    v.push_back("name3");
    v.push_back("name4");
    v[2] = "test99";
    CHECK(v[2] == "test99");
  }

  SECTION("5. copy constructor") {
    simple_vector<char> v;
    v.push_back('a');
    v.push_back('b');
    v.push_back('c');
    simple_vector<char> v1(v);
    CHECK(v.size() == v1.size());
    CHECK(v.capacity() == v1.capacity());
    CHECK(v1[1] == 'b');
  }
}
