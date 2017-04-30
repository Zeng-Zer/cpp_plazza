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

static std::shared_ptr<ICommunication> *g_ptr;

Plazza::Plazza(int nbThread) : _nbThread(nbThread), _threadId(0), _stopped(false) {
  // handle child death
  static auto handler = [this] (int sig) {
    pid_t pid;
    int status;

    while ((pid = waitpid(-1, &status, WNOHANG)) != -1) {
      std::cout << "process deleted" << std::endl;
      deleteProcess(pid);
    }
    if (sig == SIGABRT || sig == SIGSEGV) {
      *g_ptr = std::shared_ptr<ICommunication>(nullptr);
    }
  };

  struct sigaction sa;

  bzero(&sa, sizeof(struct sigaction));
  sa.sa_handler = [] (int sig) {
    handler(sig);
  };
  sa.sa_flags = SA_RESTART;

  sigaction(SIGCHLD, &sa, NULL);
  sigaction(SIGSEGV, &sa, NULL);
  sigaction(SIGABRT, &sa, NULL);
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

  _stopped = true;
  while (!_processes.empty());
}

bool Plazza::stopped() const {
  return _stopped;
}

void Plazza::processTask(Task const& task) {
  std::vector<std::pair<int, pid_t>> status = getProcessesStatus();
  int min = _nbThread * 2 + 1;
  pid_t pid = -1;

  int i = 0;
  for (auto const& thread : status) {
    std::cout << "process: " << i++ << ", nb of thread working: " << thread.first << "/" << _nbThread * 2 << std::endl;
  }

  for (auto const& stat : status) {
    if (stat.first < _nbThread * 2) {
      if (stat.first < min) {
	min = stat.first;
	pid = stat.second;
      }
    }
  }

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

std::vector<std::pair<int, pid_t>> Plazza::getProcessesStatus() {
  std::vector<std::pair<int, pid_t>> ret;
  for (auto const& process : _processes) {
    Package pkg = {OCCUPIED_SLOT, .content = {.value = -1}};
    std::shared_ptr<ICommunication> com = process.second;

    _interacting.lock();
    com->sendMsg(pkg);
    g_ptr = &com;
    Package res = com->receiveMsg();
    while (res.type == UNDEFINED && !_stopped) {
      if (!com) {
	return ret;
      }
      res = com->receiveMsg();
    }
    _interacting.unlock();

    ret.push_back({res.content.value, process.first});
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
    Package res;
    *com >> res;
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


void Plazza::lock() {
  _ui.lock();
}

void Plazza::unlock() {
  _ui.unlock();
}
