#ifndef PROCESS_HPP_
# define PROCESS_HPP_

# include <memory>
# include <vector>
# include <thread>
# include <mutex>
# include <condition_variable>
# include "Option.hpp"
# include "Task.hpp"
# include "ICommunication.hpp"
# include "BlockingQueue.hpp"

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
  void createThread(int id); // TODO TBD PARAMETER

  /**
   * check whether the process can get another task or not
   */
  bool isFull() const;

  /**
   * Receive task
   */
  Option<Task> receiveTask() const;

  /**
   * stop the current process
   * timeout suicide
   * kill thead and kill itself
   */
  void stop();

  /**
   * check whether the process is working or not
   */
  bool isWorking() const;

private:
  std::unique_ptr<ICommunication> _com;
  int const _nbThread;
  BlockingQueue<Task> _tasks;
  std::vector<std::thread> _threads;
  std::vector<bool> _thEmpty;
  std::mutex _mutex;
  bool _running;
};

#endif /* !PROCESS_HPP_ */
