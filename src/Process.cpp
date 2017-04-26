#include <unistd.h>
#include <chrono>
#include "Process.hpp"

Process::Process(int nbThread) : _nbThread(nbThread) {
  _pid = fork();
}

Process::~Process() {

}

void Process::run() {
  // TODO CREATE THREAD HERE
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
      // TODO lock queue mutex
      pushCommand(*task);
      start = now;
    }

    // timeout if it hasn't been working for 5 seconds
    if (!_tasks.empty()) {
      start = now;
    } else if ((now - start).count() >= 5) {
      timeoutSuicide();
    }

    usleep(20);
  }
}

pid_t Process::getPid() const {
  return _pid;
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
  return Option<Task>();
}

void Process::timeoutSuicide() {

}
