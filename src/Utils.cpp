#include "Utils.hpp"

Option<int> Utils::getNumber(std::string const& str) {
  try {
    return Option<int>(std::stoi(str));
  } catch (std::invalid_argument const& e) {
    return Option<int>();
  }
}
