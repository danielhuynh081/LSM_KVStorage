#pragma once

#include <string>
#include <utility>

namespace lsm {

// Represents the result of an operation that can fail. Used instead of
// exceptions throughout the store so callers must explicitly check outcomes.
class Status {
 public:
  enum class Code {
    kOk,
    kNotFound,
    kIOError,
    kCorruption,
    kInvalidArgument,
  };

  Status() : code_(Code::kOk) {}

//Status Functions
  static Status OK() { return Status(Code::kOk, ""); }
  static Status NotFound(std::string msg = "") { return Status(Code::kNotFound, std::move(msg)); }
  static Status IOError(std::string msg = "") { return Status(Code::kIOError, std::move(msg)); }
  static Status Corruption(std::string msg = "") { return Status(Code::kCorruption, std::move(msg)); }
  static Status InvalidArgument(std::string msg = "") { return Status(Code::kInvalidArgument, std::move(msg)); }

//Status Checks
  bool ok() const { return code_ == Code::kOk; }
  bool IsNotFound() const { return code_ == Code::kNotFound; }
  bool IsIOError() const { return code_ == Code::kIOError; }
  bool IsCorruption() const { return code_ == Code::kCorruption; }
  bool IsInvalidArgument() const { return code_ == Code::kInvalidArgument; }


  Code code() const { return code_; }
  const std::string& message() const { return message_; }

  std::string ToString() const {
    if (ok()) return "OK";
    return CodeName(code_) + ": " + message_;
  }

 private:
  Status(Code code, std::string message) : code_(code), message_(std::move(message)) {}

  static std::string CodeName(Code code) {
    switch (code) {
      case Code::kOk: return "OK";
      case Code::kNotFound: return "NotFound";
      case Code::kIOError: return "IOError";
      case Code::kCorruption: return "Corruption";
      case Code::kInvalidArgument: return "InvalidArgument";
    }
    return "Unknown";
  }

  Code code_;
  std::string message_;
};

}  // namespace lsm