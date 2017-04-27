#include <unistd.h>
#include <chrono>
#include "Process.hpp"

Process::Process(int nbThread) : _nbThread(nbThread) {
}

Process::~Process() {

}

void Process::run() {
  for (int i = 0; i < _nbThread; ++i) {
    createThread();
  }

  std::chrono::time_point<std::chrono::system_clock> start;
  start = std::chrono::system_clock::now();

  while (1) {
    std::chrono::time_point<std::chrono::system_clock> now;
    now = std::chrono::system_clock::now();

    Option<Task> task = receiveTask();

    // process task here
    if (task) {
      _mutex.lock();
      pushCommand(*task);
      _mutex.unlock();
      start = now;
    }

    // timeout if it hasn't been working for 5 seconds
    if (!_tasks.empty()) { // TODO ADD CONDITION VAR ?
      start = now;
    } else if (std::chrono::duration_cast<std::chrono::seconds>(now - start).count() >= 5) {
      timeoutSuicide();
    }

  }
}

void Process::createThread() { // TODO TBD PARAMETER

}

bool Process::isFull() const {
  return _tasks.size() >= (_nbThread * 2ul);
}

void Process::pushCommand(Task const& task) {
  _tasks.push(task);
}

Option<Task> Process::receiveTask() const {
  return {};
}

void Process::timeoutSuicide() {
  std::cout << "suicide" << std::endl;
  exit(0);
}
