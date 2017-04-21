#ifndef UTILS_HPP_
# define UTILS_HPP_

# include "Option.hpp"

namespace Utils {
  Option<int> getNumber(std::string const& str);
}

#endif /* !UTILS_HPP_ */
