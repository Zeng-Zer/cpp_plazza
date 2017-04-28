#include "Fork.hpp"

Fork::Fork(std::function<void()>f) {
  _pid = fork();
  if (_pid == 0) {
    f();
  }
}

Fork::~Fork() {

}

pid_t Fork::getPid() const {
  return _pid;
}
