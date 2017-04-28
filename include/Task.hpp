#ifndef TASK_HPP_
# define TASK_HPP_

# include <vector>
# include <string>
# include <map>

enum Information {
  PHONE_NUMBER,
  EMAIL_ADDRESS,
  IP_ADDRESS
};

/**
 * Structure defining a task to be sent to processes
 */
struct Task {
  std::string file;
  Information info;
};

namespace Info {
  extern std::map<std::string, Information> const infos;
  Information fromString(std::string const& str);
};

enum PackageType {
  TASK,
  OCCUPIED_SLOT,
  QUIT,
};

/**
 * structure to pass around ICommunication
 */
struct Package {
  // type of the package
  PackageType type;

  // content of the package
  union {
    Task task();
    long value;
  } content;
};

#endif /* !TASK_HPP_ */
