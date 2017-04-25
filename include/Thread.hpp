#ifndef THREAD_HPP_
# define THREAD_HPP_

class Thread {
public:
  Thread();
  ~Thread();

  /**
   * Method that is called when the thread is started
   */
  void run();

  bool isRunning() const;

private:
  bool _running;
};

#endif /* !THREAD_HPP_ */
