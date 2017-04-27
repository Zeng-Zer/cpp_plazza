#include "Exception.hpp"

Exception::Exception(std::string const& msg) : _msg(msg) {
}

Exception::~Exception() {
}

char const *Exception::what() const throw() {
  return _msg.c_str();
}

InformationException::InformationException(std::string const& msg) : Exception(msg) {
}

ProcessException::ProcessException(std::string const& msg) : Exception(msg) {
}
