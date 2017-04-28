#include <iostream>
#include "Utils.hpp"
#include "Plazza.hpp"
#include "Exception.hpp"

static int getParamThread(int argc, char *argv[]) {
  if (argc != 2) {
    std::cerr << "Usage: " << argv[0] << " [NB_THREAD]" << std::endl;
    return -1;
  }

  Option<int> nbThread = Utils::getOptNumber(argv[1]);
  if (!nbThread) {
    std::cerr << "\"" << argv[1] << "\" is not a number" << std::endl;
    return -1;
  }

  if (*nbThread < 1) {
    std::cerr << *nbThread << " must be superior of 1" << std::endl;
    return -1;
  }

  return *nbThread;
}

int main(int argc, char *argv[]) {
  int nbThread = getParamThread(argc, argv);
  if (nbThread == -1) {
    return -1;
  }

  Plazza plazza(nbThread);

  plazza.parseSTDIN();

  while (plazza.isRunning()) {
    Option<Task> task = plazza.getNextTask();
    if (!task) {
      continue;
    }

    pid_t process = plazza.getAvailableProcess();
    if (process == -1) {
      try {
	process = plazza.createProcess();
      } catch (ProcessException const& e) {
	std::cerr << e.what() << std::endl;
      }
    }

    plazza.sendTask(process, *task);
  }

  std::cout << "end" << std::endl;
  return 0;
}
