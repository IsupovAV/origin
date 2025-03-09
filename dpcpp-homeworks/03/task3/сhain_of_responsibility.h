#pragma once

#include <fstream>
#include <iostream>
#include <map>
#include <memory>
#include <optional>
#include <stdexcept>
#include <vector>

enum class Type { Warning, Error, FatalError, Unknown };

const std::string warning = "warning handled";
const std::string error = "error handled";
const std::string fatal = "fatal error handled";
const std::string unknown = "unknown handled";

class LogMessage {
public:
  LogMessage(Type type_message, const std::string &message)
      : type_message_(type_message), message_(message) {}

  Type type() const { return type_message_; };

  const std::string &message() const { return message_; };

private:
  Type type_message_;
  std::string message_;
};

class Handler {
public:
  void handle_request(const LogMessage &msg);

protected:
  virtual void handle_message(const LogMessage &msg) = 0;
  virtual Type on_handle() const = 0;
  std::shared_ptr<Handler> next_;
};

class WarningMessageHandler : public Handler {
public:
  WarningMessageHandler(std::shared_ptr<Handler> next);

protected:
  void handle_message(const LogMessage &msg) override;
  Type on_handle() const override;
};

class ErrorMessageHandler : public Handler {
public:
  ErrorMessageHandler(std::string path, std::shared_ptr<Handler> next);

protected:
  void handle_message(const LogMessage &msg) override;
  Type on_handle() const override;

private:
  std::string path_;
};

class FatalErrorMessageHandler : public Handler {
public:
  FatalErrorMessageHandler(std::shared_ptr<Handler> next);

protected:
  void handle_message(const LogMessage &msg) override;

  Type on_handle() const override;
};

class UnknownMessageHandler : public Handler {
protected:
  void handle_message(const LogMessage &msg) override;
  Type on_handle() const override;
};
