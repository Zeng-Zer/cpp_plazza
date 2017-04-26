#include <csignal>
#include <sys/wait.h>
#include <string.h>
#include "Plazza.hpp"

Plazza::Plazza(int nbThread) : _nbThread(nbThread) {
  // handle child death
  static auto handler = [this] (int) {
    pid_t pid;
    int status;

    while ((pid = waitpid(-1, &status, WNOHANG)) != -1) {
      deleteProcess(pid);
    }
  };

  struct sigaction sa;

  bzero(&sa, sizeof(struct sigaction));
  sa.sa_handler = [] (int sig) {
    handler(sig);
  };

  sigaction(SIGCHLD, &sa, NULL);
}

Plazza::~Plazza() {

}

void Plazza::createProcess() {
  Process process(_nbThread);
  std::unique_ptr<ICommunication> com; // TODO open a socket ?

  if (process.getPid() == 0) {
    // child process here
    process.run();
    exit(0);
  } else {
    // parent process
    _processes[process.getPid()] = std::move(com);
  }
}

// TODO SEND TASK
void Plazza::sendTask(pid_t process, Task const& task) const {
  (void)process;
  (void)task;
}

void Plazza::deleteProcess(pid_t pid) {
  std::unique_ptr<ICommunication> com = std::move(_processes[pid]);

  _processes.erase(_processes.find(pid));
  com->close();
}

pid_t Plazza::getAvailableProcess() const {
  // TODO GET AVAILABLE PROCESS
  return -1;
}

// TODO read stdin
Option<Task> Plazza::readTask() const {
  return Option<Task>();
}

// TODO IS PROCESS FULL
bool Plazza::isProcessFull(pid_t pid) const {
  (void)pid;
  return true;
}
