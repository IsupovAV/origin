// task3.cpp : Паттерн «Цепочка ответственности»
#include "сhain_of_responsibility.h"

int main() {

  const std::string path = "log_fаile.txt";

  LogMessage msg_warning(Type::Warning, warning);
  LogMessage msg_error(Type::Error, error);
  LogMessage msg_fatal_error(Type::FatalError, fatal);
  LogMessage msg_unknown(Type::Unknown, unknown);

  auto handle_unknown = std::make_shared<UnknownMessageHandler>();
  auto handle_warning = std::make_shared<WarningMessageHandler>(handle_unknown);
  auto handle_error =
      std::make_shared<ErrorMessageHandler>(path, handle_warning);
  auto handle_fatal_error =
      std::make_shared<FatalErrorMessageHandler>(handle_error);

  try {
    handle_fatal_error->handle_request(msg_fatal_error);
    handle_error->handle_request(msg_error);
    handle_warning->handle_request(msg_warning);
    handle_unknown->handle_request(msg_unknown);
  } catch (const std::exception &e) {
    std::cout << e.what() << std::endl;
  }

  return 0;
}
