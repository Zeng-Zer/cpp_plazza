#include "Communication.hpp"
#include <iostream>

int main()
{
  Communication yolo(0);

  Package test;

  test.type = QUIT;
  test.content.value = 10000;

  int pid = fork();
  if (pid == 0)
    {
      usleep(10000);
      std::cout << "child" << std::endl;
      yolo.openCommunicationChild();
      Package testo = yolo.receiveMsg();
      if (!(testo.type == UNDEFINED || test.content.value == -1))
	std::cout << testo.content.value << std::endl;
    }
  else
    {
      std::cout << "parent" << std::endl;
      yolo.openCommunicationMain();
      yolo.sendMsg(test);
    }
  yolo.close();
  yolo.rmfifo();
  return (0);
}
