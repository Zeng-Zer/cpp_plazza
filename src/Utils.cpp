#include "Utils.hpp"

Option<int> Utils::getOptNumber(std::string const& str) {
  try {
    return Option<int>(std::stoi(str));
  } catch (std::invalid_argument const& e) {
    return Option<int>();
  }
}
