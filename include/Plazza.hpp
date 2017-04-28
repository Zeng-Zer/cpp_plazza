#ifndef PLAZZA_HPP_
# define PLAZZA_HPP_

# include <memory>
# include <map>
# include <unistd.h>
# include <thread>
# include <mutex>
# include "Option.hpp"
# include "Task.hpp"
# include "ICommunication.hpp"
# include "BlockingQueue.hpp"

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
  pid_t createProcess();

  /**
   * send a package to the process
   */
  void sendPkg(pid_t process, Package pkg) const;

  /**
   * send task to a process
   */
  void sendTask(pid_t process, Task const& task) const;

  /**
   * delete a process by its pid
   */
  void deleteProcess(pid_t pid);

  /**
   * kill the process
   */
  void killProcess(pid_t pid);

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

  /**
   * pop next task from the queue
   */
  Option<Task> getNextTask();

  /**
   * return true if the program completed all of its tasks
   */
  bool isRunning() const;

private:
  /**
   * parse string to get the next tasks
   */
  std::vector<Task> readTask(std::string const& line) const;

private:
  int const _nbThread;
  BlockingQueue<Task> _tasks;
  std::map<pid_t, std::unique_ptr<ICommunication>> _processes;
  std::thread _producer;

  bool _finished;
};

#endif /* !PLAZZA_HPP_ */
