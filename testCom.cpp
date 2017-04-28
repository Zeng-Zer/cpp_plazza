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
      usleep(10000);
      std::cout << "receiving" << std::endl;
      Package testo;
      testo = yolo.receiveMsg();
      std::cout << "received!" << std::endl;
      if (!(testo.type == UNDEFINED || test.content.value == -1))
	std::cout << testo.content.value << std::endl;
      else
      	std::cout << "yolo-fzepojfzep" << std::endl;
    }
  else
    {
      std::cout << "parent" << std::endl;
      yolo.openCommunicationMain();
      std::cout << "sending" << std::endl;
      yolo.sendMsg(test);
      usleep(999999);
    }
  yolo.close();
  yolo.rmfifo();
  return (0);
}
