#pragma once
#include <stdexcept>
#include <string>

struct ProtocoloError : public std::runtime_error {
  explicit ProtocoloError(const std::string &message)
      : std::runtime_error(message) {}
};

struct SocketClose : public std::runtime_error {
  SocketClose() : std::runtime_error("") {}
};
