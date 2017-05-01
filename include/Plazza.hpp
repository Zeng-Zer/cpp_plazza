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
   * run the whole plazza program
   */
  void run();

  /**
   * getter for _stopped
   */
  bool stopped() const;

  /**
   * get processes status
   */
  std::vector<std::pair<int, pid_t>> getStatus() const;

private:
  /**
   * parse stdin for tasks
   */
  void parseSTDIN();

  /**
   * get process status
   */
  std::vector<std::pair<int, pid_t>> getProcessesStatus();

  /**
   * create a new process
   */
  pid_t createProcess();

  /**
   * send task to a process
   */
  void sendTask(pid_t process, Task const& task) const;

  /**
   * delete a process by its pid
   */
  void deleteProcess(pid_t pid);

  /**
   * kill every process
   */
  void killAll();

  /**
   * process task
   */
  void processTask(Task const& task);

  /**
   * parse string to get the next tasks
   */
  std::vector<Task> readTask(std::string const& line) const;

private:
  int const _nbThread;
  std::map<pid_t, std::shared_ptr<ICommunication>> _processes;
  long _threadId;
  bool _stopped;
  BlockingQueue<Task> _tasks;
  std::thread _stdin;
  std::vector<std::pair<int, pid_t>> _status;
  bool _deleted;
};

#endif /* !PLAZZA_HPP_ */
