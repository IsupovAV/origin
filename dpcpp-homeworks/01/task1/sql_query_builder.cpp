#include "sql_query_builder.h"
#include <algorithm>

SqlSelectQueryBuilder &
SqlSelectQueryBuilder::AddColumn(const std::string &column) {
  this->columns_.emplace(column);
  return *this;
}

SqlSelectQueryBuilder &SqlSelectQueryBuilder::AddFrom(const std::string from) {
  from_ = from;
  return *this;
}

SqlSelectQueryBuilder &
SqlSelectQueryBuilder::AddWhere(const std::string where_key,
                                const std::string where_par) {
  where_[where_key] = where_par;

  return *this;
}

std::string SqlSelectQueryBuilder::BuildQuery() {
  query_ = "SELECT ";
  if (!columns_.empty()) {
    std::for_each(columns_.begin(), columns_.end(),
                  [&](std::string e) { query_ += (e + ", "); });
    auto pos = query_.size() - 2;
    query_.erase(pos, 1);

  } else {
    query_ += "* ";
  }
  query_ += "FROM " + from_;
  if (!where_.empty()) {
    query_ += " WHERE ";
    for (auto &[key, val] : where_) {
      query_ += key + "=" + val + " AND ";
    }
    auto pos = query_.size() - 5;
    query_.erase(pos);
  }
  query_ += ";";

  return query_;
}
