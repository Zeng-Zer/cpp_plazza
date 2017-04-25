#ifndef PLAZZA_HPP_
# define PLAZZA_HPP_

# include <memory>
# include <vector>
# include <unistd.h>
# include "Process.hpp"
# include "Task.hpp"

class Plazza {
public:
  Plazza(int nbThread);
  ~Plazza();

  /**
   * create a new process
   */
  void createProcess(); // TODO TBD PARAMETER

  /**
   * send task to a process
   */
  void sendTask(pid_t process, Task const& task);



private:
  int const _nbThread;
  std::vector<pid_t> _processes;
};

#endif /* !PLAZZA_HPP_ */
