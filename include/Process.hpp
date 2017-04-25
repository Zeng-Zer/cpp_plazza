#ifndef PROCESS_HPP_
# define PROCESS_HPP_

# include <memory>
# include <vector>
# include <queue>
# include "Option.hpp"
# include "Thread.hpp"
# include "Task.hpp"

/**
 * Class that encapsulate a process
 */
class Process {
public:
  Process(int nbThread);
  ~Process() = default;

  /**
   * main method
   */
  void run();

private:
  /**
   * create a thread
   */
  void createThread(); // TODO TBD PARAMETER

  /**
   * check whether the process can get another task or not
   */
  bool isFull() const;

  /**
   * Push task to _tasks queue
   */
  void pushCommand(Task const& task);

  /**
   * Receive task
   */
  Option<Task> receiveTask();

private:
  int const _nbThread;
  std::queue<Task> _tasks;
  std::vector<std::shared_ptr<Thread>> _threads;
};

#endif /* !PROCESS_HPP_ */
