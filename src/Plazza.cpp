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

Plazza::Plazza(int nbThread) : _nbThread(nbThread), _finished(true) { // TODO set finished to false
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

pid_t Plazza::createProcess() {
  std::cout << "new process" << std::endl;
  std::unique_ptr<ICommunication> com(new Communication(_processes.size() * 2));
  Fork process;

  // fork failed
  if (process.getPid() == -1) {
    throw ProcessException("Process initialization failed");
  }
  // child process here
  else if (process.getPid() == 0) {
    int nb = _nbThread;
    com->openCommunicationChild();
    process.run([&com, nb] () {
	Process proc(nb, com);
	proc.run();
      });
    exit(0);
  }
  // parent process
  else {
    com->openCommunicationMain();
    _processes[process.getPid()] = std::move(com);
    return process.getPid();
  }
}

void Plazza::sendPkg(pid_t process, Package pkg) const {
  std::unique_ptr<ICommunication> const& com = _processes.at(process);
  com->sendMsg(pkg);
}

void Plazza::sendTask(pid_t process, Task const& task) const {
  Package pkg = {TASK, .content = {.task = task}};

  sendPkg(process, pkg);
}

void Plazza::deleteProcess(pid_t pid) {
  if (!_processes.count(pid)) {
    return;
  }

  std::unique_ptr<ICommunication> com = std::move(_processes[pid]);

  _processes.erase(_processes.find(pid));
  com->close();
  com->rmfifo();
}

// TODO Kill process ?
void Plazza::killProcess(pid_t pid) {
  if (!_processes.count(pid)) {
    return;
  }
  kill(SIGTERM, pid);

  // std::unique_ptr<ICommunication> com = std::move(_processes[pid]);

  // _processes.erase(_processes.find(pid));
  // com->close();
}

pid_t Plazza::getAvailableProcess() const {
  for (auto const& process : _processes) {
    pid_t pid = process.first;
    Package pkg = {OCCUPIED_SLOT, .content = {.value = -1}};
    auto const& com = process.second;

    sendPkg(pid, pkg);
    while (pkg.content.value == -1) {
      pkg = com->receiveMsg();
    }

    if (pkg.content.value < _nbThread * 2) {
      return pid;
    }
  }
  return -1;
}

void Plazza::parseSTDIN() {
  _producer = std::thread([this] () {
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
      // notify main that the thread is done
      _producer.detach();
    });
}

Option<Task> Plazza::getNextTask() {
  return _tasks.timedPop(10);
}

bool Plazza::isRunning() const {
  return !_finished || _producer.joinable();
}

std::vector<Task> Plazza::readTask(std::string const& line) const {
  // TODO REMOVE DEBUG HERE
  std::cout << "got: " << line << std::endl;
  std::vector<std::string> tokens;
  std::string str;
  std::stringstream sstr(line);

  while ((sstr >> str)) {
    tokens.push_back(str);
  }

  if (tokens.size() <= 1) {
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
    task.info = info;
    strcpy(task.file, file.c_str());
    tasks.push_back(task);
  }

  return tasks;
}
