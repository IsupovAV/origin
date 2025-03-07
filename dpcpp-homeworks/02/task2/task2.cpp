#include <iostream>
#include <map>
#include <memory>
#include <string>

class VeryHeavyDatabase {
public:
  virtual std::string get_data(const std::string &key) noexcept {
    return "Very Big Data String: " + key;
  }
};

class CacheProxyDB : public VeryHeavyDatabase {
public:
  explicit CacheProxyDB(std::unique_ptr<VeryHeavyDatabase> real)
      : real_db_(std::move(real)) {};

  std::string get_data(const std::string &key) noexcept override {
    if (!cache_.contains(key)) {
      std::cout << "Data from real DB: ";
      cache_[key] = real_db_->get_data(key);
    } else {
      std::cout << "Data from cache: ";
    }
    return cache_.at(key);
  }

private:
  std::map<std::string, std::string> cache_;
  const std::unique_ptr<VeryHeavyDatabase> real_db_;
};

class OneShotDB : VeryHeavyDatabase {
public:
  explicit OneShotDB(VeryHeavyDatabase *real, size_t shots = 1)
      : real_db_(real), count_(1), limit_(shots) {}
  std::string GetData(const std::string &key) noexcept {
    if (count_ <= limit_) {
      ++count_;
      return real_db_->get_data(key);
    } else {
      return "error";
    }
  }

private:
  size_t count_;
  size_t limit_;
  VeryHeavyDatabase *real_db_;
};

std::unique_ptr<CacheProxyDB> create_cache() {
  auto real_db = std::make_unique<VeryHeavyDatabase>();
  return std::make_unique<CacheProxyDB>(std::move(real_db));
}

static int constexpr limit = 3;

int main() {
  system("chcp 65001");
  
  auto real = VeryHeavyDatabase();
  auto limit_db = OneShotDB(std::addressof(real), limit);
  std::cout << limit_db.GetData("Подключение 1") << std::endl;
  std::cout << limit_db.GetData("Подключение 2") << std::endl;
  std::cout << limit_db.GetData("Подключение 3") << std::endl;
  std::cout << limit_db.GetData("Подключение 4") << std::endl; //  error
  std::cout << "Превышен лимит подключений их должно быть не больше " << limit << std::endl;

  return 0;
}
