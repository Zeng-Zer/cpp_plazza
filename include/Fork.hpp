#ifndef FORK_HPP_
# define FORK_HPP_

# include <functional>
# include <unistd.h>

class Fork {
public:
  Fork(std::function<void()>f);
  ~Fork();

  /**
   * return pid
   */
  pid_t getPid() const;

private:
  pid_t _pid;
};

#endif /* !FORK_HPP_ */
