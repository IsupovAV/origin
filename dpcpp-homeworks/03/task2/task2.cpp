// task2.cpp : Паттерн «Наблюдатель»
#include <fstream>
#include <iostream>
#include <memory>
#include <vector>

class Observer {
public:
  virtual void onWarning(const std::string &message) {};
  virtual void onError(const std::string &message) {};
  virtual void onFatalError(const std::string &message) {};

protected:
  std::string path_;
  void write_to_file_(const std::string &message) const {

    std::ofstream out;
    out.exceptions(std::ofstream::badbit | std::ofstream::failbit);

    try {

      out.open(path_, std::ios::app);
    } catch (const std::ofstream::failure &ex) {
      std::cout << "error opening file" << std::endl;
      std::cout << ex.what() << std::endl;
    }

    if (!out.is_open()) {
      std::cout << "error opening file" << std::endl;
    } else {
      out << message << std::endl;
    }
    out.close();
  }
};

class ObserverWarning : public Observer {
public:
  void onWarning(const std::string &message) override {

    std::cout << message << std::endl;
  }
};

class ObserverError : public Observer {
public:
  ObserverError(const std::string &path) { path_ = path; };

  void onError(const std::string &message) override { write_to_file_(message); }
};

class ObserverFatalError : public Observer {
public:
  ObserverFatalError(const std::string &path) { path_ = path; };

  void onFatalError(const std::string &message) override {
    std::cout << message << std::endl;
    write_to_file_(message);
  }
};

class Publisher {
public:
  void warning(const std::string &message) const {
    notify_(&Observer::onWarning, message);
  }

  void error(const std::string &message) const {
    notify_(&Observer::onError, message);
  }

  void fatal_error(const std::string &message) const {
    notify_(&Observer::onFatalError, message);
  }

  void add_observer(std::weak_ptr<Observer> observer) {
    observers_.push_back(std::move(observer));
  }

private:
  void notify_(void (Observer::*ptr)(const std::string &),
               const std::string &message) const {
    for (std::weak_ptr<Observer> observer : observers_) {
      if (std::shared_ptr<Observer> s_ptr = observer.lock())
        (s_ptr.get()->*ptr)(message);
    }
  }

  std::vector<std::weak_ptr<Observer>> observers_;
};

int main() {
  const std::string path = "errors_log.txt";
  Publisher pub;

  auto w_observer = std::make_shared<ObserverWarning>();
  auto e_observer = std::make_shared<ObserverError>(path);
  auto f_observer = std::make_shared<ObserverFatalError>(path);

  pub.add_observer(w_observer);
  pub.add_observer(e_observer);
  pub.add_observer(f_observer);

  pub.warning("message triggered by event onWarning");
  pub.error("message triggered by event onError");
  pub.fatal_error("message triggered by event onFatalError");

  return 0;
}
