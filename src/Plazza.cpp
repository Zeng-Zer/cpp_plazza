#include <csignal>
#include <sys/wait.h>
#include <string.h>
#include <sstream>
#include <algorithm>
#include "Plazza.hpp"
#include "Utils.hpp"

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

void Plazza::parseSTDIN() {
  std::string line;
  std::string cmd;

  while (getline(std::cin, line)) {
    std::istringstream ss(line);

    while (getline(ss, cmd, ';')) {
      cmd = Utils::trim(cmd);

      std::vector<Task> tasks = readTask(cmd);
      std::for_each(tasks.begin(), tasks.end(), [this] (Task const& task) {
	  _tasks.push(task);
	});
    }

  }
}

// TODO read stdin
std::vector<Task> Plazza::readTask(std::string const& line) const {
  // TODO REMOVE THIS DEBUG
  std::cout << line << std::endl;

  return {};
}

// TODO IS PROCESS FULL
bool Plazza::isProcessFull(pid_t pid) const {
  (void)pid;
  return true;
}
