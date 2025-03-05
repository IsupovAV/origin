#include "sql_query_builder.h"
#include <iostream>

void tests() {
  int cnt = 0;
  int constexpr all_tests = 2;
  {
    // test1 проверяем добавленный метод
    // SqlSelectQueryBuilder& AddWhere(const std::map<std::string, std::string>& kv) noexcept;
    SqlSelectQueryBuilder query_builder;
    query_builder.AddColumn("name")
        .AddColumn("phone")
        .AddColumn("speciality")
        .AddFrom("students")
        .AddWhere({{"id", "42"},
                   {"name", "John"},
                   {"speciality", "C++"},
                   {"phone", "+7950-456-7534"}});
    const std::string test1 =
        "SELECT name, phone, speciality FROM students WHERE id=42 AND "
        "name=John AND phone=+7950-456-7534 AND speciality=C++;";
    if (query_builder.BuildQuery() == test1) {
      std::cout << "test1 ok" << std::endl;
      ++cnt;
    } else {
      std::cout << "test1 error" << std::endl;
    }
  }

  {
    // test2 проверяем добавленный метод
    // SqlSelectQueryBuilder &AddColumns(const std::vector<std::string> &columns) noexcept;
    SqlSelectQueryBuilder query_builder1;
    query_builder1.AddColumns({"name", "phone", "speciality"})
        .AddWhere({{"id", "42"}, {"name", "John"}})
        .AddFrom("students");
    const std::string test2 = "SELECT name, phone, speciality FROM students "
                              "WHERE id=42 AND name=John;";
    if (query_builder1.BuildQuery() == test2) {
      std::cout << "test2 ok" << std::endl;
      ++cnt;
    } else {
      std::cout << "test2 error" << std::endl;
    }
  }

  if (cnt == all_tests) {
    std::cout << "All " << all_tests
              << " tests completed successfully " << std::endl;
  } else {
    std::cout << cnt << " tests completed successfully" << std::endl;
    std::cout << all_tests - cnt << " tests failed" << std::endl;

  }
}

int main() {
  tests();

  return 0;
}
