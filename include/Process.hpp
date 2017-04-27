#ifndef PROCESS_HPP_
# define PROCESS_HPP_

# include <memory>
# include <vector>
# include <queue>
# include <thread>
# include <mutex>
# include "Option.hpp"
# include "Task.hpp"
# include "ICommunication.hpp"

/**
 * Class that encapsulate a process
 */
class Process {
public:
  Process(int nbThread);
  ~Process();

  /**
   * main method: producer
   */
  void run();

private:
  /**
   * create a thread: consumer
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
  Option<Task> receiveTask() const;

  /**
   * timeout suicide
   * kill thead and kill itself
   */
  void timeoutSuicide();

private:
  std::unique_ptr<ICommunication> _com;
  int const _nbThread;
  std::queue<Task> _tasks;
  std::vector<std::thread> _threads;
  std::mutex _mutex;
};

#endif /* !PROCESS_HPP_ */
