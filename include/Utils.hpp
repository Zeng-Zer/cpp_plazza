#ifndef UTILS_HPP_
# define UTILS_HPP_

# include "Option.hpp"

/**
 * Util functions go here
 */
namespace Utils {
  Option<int> getOptNumber(std::string const& str);
  std::string trim(std::string str);
}

#endif /* !UTILS_HPP_ */
