#include "сhain_of_responsibility.h"

void Handler::handle_request(const LogMessage &msg) {
  if (on_handle() == msg.type()) {
    handle_message(msg);
  } else if (next_) {
    next_->handle_request(msg);
  } else {
    throw(std::runtime_error("error: handler for this message not found!"));
  }
};

WarningMessageHandler::WarningMessageHandler(std::shared_ptr<Handler> next) {
  next_ = (std::move(next));
};

void WarningMessageHandler::handle_message(const LogMessage &msg) {
  std::cout << msg.message() << std::endl;
};

Type WarningMessageHandler::on_handle() const { return Type::Warning; };

ErrorMessageHandler::ErrorMessageHandler(std::string path,
                                         std::shared_ptr<Handler> next) {
  path_ = (path);
  next_ = (std::move(next));
}

void ErrorMessageHandler::handle_message(const LogMessage &msg) {
  std::ofstream out;
  out.exceptions(std::ofstream::badbit | std::ofstream::failbit);

  try {
    out.open(path_, std::ofstream::app);
  } catch (const std::ofstream::failure &ex) {
    std::cout << "error opening file" << std::endl;
    std::cout << ex.what() << std::endl;
  }

  if (!out.is_open()) {
    std::cout << "error opening file" << std::endl;
  } else {
    out << msg.message() << std::endl;
  }

  out.close();
}

Type ErrorMessageHandler::on_handle() const { return Type::Error; }

FatalErrorMessageHandler::FatalErrorMessageHandler(
    std::shared_ptr<Handler> next) {
  next_ = (std::move(next));
}

void FatalErrorMessageHandler::handle_message(const LogMessage &msg) {

  throw(std::runtime_error(msg.message()));
}

Type FatalErrorMessageHandler::on_handle() const { return Type::FatalError; }

void UnknownMessageHandler::handle_message(const LogMessage &msg) {
  throw(std::runtime_error(msg.message()));
}

Type UnknownMessageHandler::on_handle() const { return Type::Unknown; }
