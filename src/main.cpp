#include <iostream>
#include "Utils.hpp"
#include "Plazza.hpp"
#include "Exception.hpp"
#ifdef UI
# include "Ui.hpp"
#endif

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

#ifdef UI
  std::thread th([&plazza, nbThread] () {
      Ui gui;
      gui.create();

      // main loop
      while (1) {
	std::vector<int> status = plazza.getProcessesStatus();
	if (plazza.stopped()) {
	  return;
	}

	for (int i : status) {
	  std::cout << "process: " << i << ", nb of thread working: " << i << "/" << nbThread * 2 << std::endl;
	}

	gui.update();
      }

    });
#endif

  plazza.run();
#ifdef UI
  th.join();
#endif

  return 0;
}
