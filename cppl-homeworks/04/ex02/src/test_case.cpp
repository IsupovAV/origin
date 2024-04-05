#include <catch2/catch_all.hpp>
#include "list.h"

TEST_CASE("Checking the functions of adding and getting items from a doubly-linked list") {
  List list;

  SECTION("1. PushBack check"){
    CHECK(list.Empty() == true);
    list.PushBack(1);
    list.PushBack(2);
    list.PushBack(3);
    CHECK(list.Size() == 3);
    CHECK(list.PopBack() == 3);
    CHECK(list.Size() == 2);
    list.PushBack(4);
    list.PopBack();
    CHECK(list.PopBack() == 2);
    CHECK(list.PopBack() == 1);
  }

  SECTION("2. PushFront check"){
    CHECK(list.Empty() == true);
    list.PushFront(1);
    list.PushFront(2);
    list.PushFront(3);
    CHECK(list.Size() == 3);
    CHECK(list.PopBack() == 1);
    CHECK(list.PopFront() == 3);
    CHECK(list.Size() == 1);
    CHECK(list.PopFront() == 2);
    CHECK(list.Size() == 0);
    list.PushFront(99);
  }

  SECTION("3. PopBack check empty list"){
    REQUIRE_THROWS_AS(list.PopBack(), std::runtime_error);
  }

  SECTION("4. PopFront check empty list"){
    list.PushBack(99);
    list.PopBack();
    REQUIRE_THROWS_AS(list.PopFront(), std::runtime_error);
  }
}

