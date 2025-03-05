#pragma once
#include <map>
#include <set>
#include <string>
#include <vector>

class SqlSelectQueryBuilder {
public:
  SqlSelectQueryBuilder() = default;
  ~SqlSelectQueryBuilder() = default;
  SqlSelectQueryBuilder &AddColumn(const std::string &column);
  SqlSelectQueryBuilder &AddFrom(const std::string from);
  SqlSelectQueryBuilder &AddWhere(const std::string where_key,
                                  const std::string where_par);
  std::string BuildQuery();

  SqlSelectQueryBuilder &
    AddWhere(const std::map<std::string, std::string> &kv) noexcept;
  SqlSelectQueryBuilder &
    AddColumns(const std::vector<std::string> &columns) noexcept;

private : 
  std::string from_;
  std::set<std::string> columns_;
  std::map<std::string, std::string> where_;
  std::string query_;
};
