#ifndef TASK_HPP_
# define TASK_HPP_

# include <vector>
# include <string>

enum Information {
  PHONE_NUMBER,
  EMAIL_ADDRESS,
  IP_ADDRESS
};

/**
 * Structure defining a task to be sent to processes
 */
struct Task {
  std::vector<std::string> files;
  Information info;
};

#endif /* !TASK_HPP_ */
