#include <unistd.h>
#include <chrono>
#include "Process.hpp"

Process::Process(int nbThread) : _nbThread(nbThread) {
}

Process::~Process() {

}

void Process::run() {
  using namespace std::chrono;
  for (int i = 0; i < _nbThread; ++i) {
    createThread();
  }

  time_point<system_clock> start;
  start = system_clock::now();

  while (1) {
    time_point<system_clock> now;
    now = system_clock::now();

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
    } else if (duration_cast<milliseconds>(now - start).count() >= 5000) {
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
