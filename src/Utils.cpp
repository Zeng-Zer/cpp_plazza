#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "Utils.hpp"

Option<int> Utils::getOptNumber(std::string const& str) {
  try {
    return Option<int>(std::stoi(str));
  } catch (std::invalid_argument const& e) {
    return Option<int>();
  }
}

/**
 *  trim : epure str equivalent delete whitespace before and after expression
 */
std::string Utils::trim(std::string str) {
  // left trim and right trim
  size_t startPos = str.find_first_not_of(" \t");
  if (startPos != std::string::npos) {
    str = str.substr(startPos);
  }

  size_t endPos = str.find_last_not_of(" \t");
  if (endPos != std::string::npos) {
    str = str.substr(0, endPos + 1);
  }

  if (str.find_first_not_of(" \t") == std::string::npos) {
    str = "";
  }
  return str;
}

bool Utils::isDirectory(std::string const& file) {
  struct stat path_stat;

  stat(file.c_str(), &path_stat);
  return !S_ISREG(path_stat.st_mode);
}
