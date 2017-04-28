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
  char file[256];
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
  UNDEFINED
};

/**
 * structure to pass around ICommunication
 */
struct Package {
  // type of the package
  PackageType type;

  // content of the package
  union Content {
    Task task;
    long value;
  } content;
};

#endif /* !TASK_HPP_ */
