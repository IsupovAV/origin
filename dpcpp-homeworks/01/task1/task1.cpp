#include "sql_query_builder.h"
#include <iostream>

void tests() {
  {
    // test1
    SqlSelectQueryBuilder query_builder;
    query_builder.AddColumn("name")
        .AddColumn("phone")
        .AddColumn("speciality")
        .AddFrom("students")
        .AddWhere("id", "42")
        .AddWhere("name", "John");
    const std::string test1 = "SELECT name, phone, speciality FROM students "
                              "WHERE id=42 AND name=John;";
    if (query_builder.BuildQuery() == test1) {
      std::cout << "test1 ok" << std::endl;
    } else {
      std::cout << "test1 error" << std::endl;
    }
  }

  {
    // test2 убираем where
    SqlSelectQueryBuilder query_builder1;
    query_builder1.AddColumn("name").AddColumn("phone").AddFrom("students");
    // query_builder1.AddWhere("id", "42").AddWhere("name", "John");
    const std::string test2 = "SELECT name, phone FROM students;";
    if (query_builder1.BuildQuery() == test2) {
      std::cout << "test2 ok" << std::endl;
    } else {
      std::cout << "test2 error" << std::endl;
    }
  }

  {
    // test3 меняем порядок вызовов
    SqlSelectQueryBuilder query_builder1;
    query_builder1.AddWhere("id", "42")
        .AddWhere("name", "John")
        .AddFrom("students")
        .AddColumn("name")
        .AddColumn("phone");
    const std::string test3 =
        "SELECT name, phone FROM students WHERE id=42 AND name=John;";
    if (query_builder1.BuildQuery() == test3) {
      std::cout << "test3 ok" << std::endl;
    } else {
      std::cout << "test3 error" << std::endl;
    }
  }

  {
    // test4 список полей пуст
    SqlSelectQueryBuilder query_builder1;
    query_builder1.AddFrom("students").AddWhere("id", "42");
    const std::string test4 = "SELECT * FROM students WHERE id=42;";
    if (query_builder1.BuildQuery() == test4) {
      std::cout << "test4 ok" << std::endl;
    } else {
      std::cout << "test4 error" << std::endl;
    }
  }

  {
    // test5 одно поле
    SqlSelectQueryBuilder query_builder1;
    query_builder1.AddColumn("name").AddFrom("students").AddWhere("id", "42");
    const std::string test5 = "SELECT name FROM students WHERE id=42;";
    if (query_builder1.BuildQuery() == test5) {
      std::cout << "test5 ok" << std::endl;
    } else {
      std::cout << "test5 error" << std::endl;
    }
  }
}

int main() {
  tests();

  return 0;
}
