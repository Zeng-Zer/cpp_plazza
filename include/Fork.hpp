#ifndef FORK_HPP_
# define FORK_HPP_

# include <functional>
# include <unistd.h>

class Fork {
public:
  Fork();
  ~Fork();

  pid_t getPid();

  /**
   * run the function give in parameter
   */
  void run(std::function<void()> f);

private:
  pid_t _pid;
};

#endif /* !FORK_HPP_ */
