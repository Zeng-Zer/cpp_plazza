#include <csignal>
#include <sys/wait.h>
#include <string.h>
#include <sstream>
#include <algorithm>
#include "Plazza.hpp"
#include "Fork.hpp"
#include "Process.hpp"
#include "Utils.hpp"
#include "Exception.hpp"
#include "Communication.hpp"

Plazza::Plazza(int nbThread) : _nbThread(nbThread), _threadId(0) {
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
  sa.sa_flags = SA_RESTART;

  sigaction(SIGCHLD, &sa, NULL);
}

Plazza::~Plazza() {
}

void Plazza::run() {
  std::string line;
  std::string cmd;

  while (getline(std::cin, line)) {
    std::istringstream ss(line);

    while (getline(ss, cmd, ';')) {
      cmd = Utils::trim(cmd);

      std::vector<Task> tasks = readTask(cmd);

      std::for_each(tasks.begin(), tasks.end(), [this] (Task const& task) {
	  processTask(task);
	});
    }

  }

  usleep(100000);
  killAll();
  usleep(100000);
}

void Plazza::processTask(Task const& task) {
  pid_t pid = getAvailableProcess();
  if (pid == -1) {
    try {
      pid = createProcess();
    } catch (ProcessException const& e) {
      std::cerr << e.what() << std::endl;
    }
  }

  sendTask(pid, task);
}

pid_t Plazza::createProcess() {
  std::shared_ptr<ICommunication> com(new Communication(_threadId++ * 2));
  int nb = _nbThread;

  // child process here
  Fork process([&com, nb] () {
      com->openCommunicationChild();
      Process proc(nb, com);
      proc.run();
      exit(0);
    });

  if (process.getPid() == -1) {
    throw ProcessException("Process initialization failed");
  } else {
    com->openCommunicationMain();
    _processes[process.getPid()] = std::move(com);
    return process.getPid();
  }
}

void Plazza::sendTask(pid_t process, Task const& task) const {
  std::shared_ptr<ICommunication> com = _processes.at(process);
  Package pkg = {TASK, .content = { .task = task }};

  com->sendMsg(pkg);
}

void Plazza::deleteProcess(pid_t pid) {
  if (!_processes.count(pid)) {
    return;
  }

  std::shared_ptr<ICommunication> com = _processes[pid];

  _processes.erase(_processes.find(pid));
  com->close();
  com->rmfifo();
}

void Plazza::killAll() {
  for (auto const& process : _processes) {
    kill(process.first, SIGTERM);
  }
}

std::vector<int> Plazza::getProcessesStatus() {
  std::vector<int> ret;
  for (auto const& process : _processes) {
    Package pkg = {OCCUPIED_SLOT, .content = {.value = -1}};
    auto const& com = process.second;

    _interacting.lock();
    com->sendMsg(pkg);
    Package res = com->receiveMsg();
    while (res.type == UNDEFINED) {
      res = com->receiveMsg();
    }
    _interacting.unlock();

    ret.push_back(res.content.value);
  }

  return ret;
}

pid_t Plazza::getAvailableProcess() {
  for (auto const& process : _processes) {
    pid_t pid = process.first;
    Package pkg = {OCCUPIED_SLOT, .content = {.value = -1}};
    auto const& com = process.second;

    _interacting.lock();
    com->sendMsg(pkg);
    Package res = com->receiveMsg();
    while (res.type == UNDEFINED) {
      res = com->receiveMsg();
    }
    _interacting.unlock();

    if (res.type == OCCUPIED_SLOT && res.content.value < _nbThread *2) {
      return pid;
    }
  }
  return -1;
}

std::vector<Task> Plazza::readTask(std::string const& line) const {
  std::vector<std::string> tokens;
  std::string str;
  std::stringstream sstr(line);

  while ((sstr >> str)) {
    tokens.push_back(str);
  }

  if (tokens.size() < 2) {
    std::cerr << "Missing information or file" << std::endl;
    return {};
  }

  Information info;
  try {
    info = Info::fromString(tokens.back());
  } catch (InformationException const& e) {
    std::cerr << e.what() << std::endl;
    return {};
  }

  tokens.pop_back();

  std::vector<Task> tasks;
  for (std::string const& file : tokens) {
    Task task;
    bzero(&task, sizeof(Task));
    task.info = info;
    strcpy(task.file, file.c_str());
    tasks.push_back(task);
  }

  return tasks;
}
