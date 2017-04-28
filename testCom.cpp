#include "Communication.hpp"
#include <iostream>

int main()
{
  Communication yolo(0);

  Package test;

  test.type = QUIT;
  test.content.value = 0;

  int pid = fork();
  if (pid == 0)
    {
      usleep(1000);
      yolo.openCommunicationChild();
      Package testo = yolo.receiveMsg();
      std::cout << testo.content.value << std::endl;
    }
  else
    {
      yolo.openCommunicationMain();
      yolo.sendMsg(test);
    }
  return (0);
}
