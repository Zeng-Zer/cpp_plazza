#include "Fork.hpp"

Fork::Fork() {
  _pid = fork();
}

Fork::~Fork() {

}

void Fork::run(std::function<void()> f) {
  f();
}

pid_t Fork::getPid() {
  return _pid;
}
