#ifndef PLAZZA_HPP_
# define PLAZZA_HPP_

# include <memory>
# include <map>
# include <unistd.h>
# include "Process.hpp"
# include "Task.hpp"
# include "ICommunication.hpp"

/**
 * Main class communicating to processes
 */
class Plazza {
public:
  Plazza(int nbThread);
  ~Plazza();

  /**
   * create a new process
   */
  void createProcess();

  /**
   * send task to a process
   */
  void sendTask(pid_t process, Task const& task) const;

  /**
   * delete a process by its pid
   */
  void deleteProcess(pid_t pid);

  /**
   * get a process that is available to work
   * return -1 if there isn't any available process
   */
  pid_t getAvailableProcess() const;

  /**
   * read tasks from stdin
   * push tasks on the queue
   */
  void parseSTDIN();

private:
  /**
   * get process status: number of tasks in the queue
   */
  bool isProcessFull(pid_t pid) const;

  /**
   * parse string to get the next tasks
   */
  std::vector<Task> readTask(std::string const& line) const;

private:
  int const _nbThread;
  std::queue<Task> _tasks;
  std::map<pid_t, std::unique_ptr<ICommunication>> _processes;
};

#endif /* !PLAZZA_HPP_ */
