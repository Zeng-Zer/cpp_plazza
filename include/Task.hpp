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
  std::string file;
  Information info;
};

/**
 * structure to pass around ICommunication
 */
union Package {
  Task task;
  long threadAvailable;
};

#endif /* !TASK_HPP_ */
