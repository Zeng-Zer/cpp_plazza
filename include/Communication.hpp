#ifndef COMMUNICATION_HPP_
# define COMMUNICATION_HPP_

#include <string>
#include <fstream>
#include <sys/stat.h>
#include <unistd.h>
#include "ICommunication.hpp"
#include "Exception.hpp"

# define PFIFO "/tmp/plazza"

class Communication : public ICommunication
{
public:
  Communication(int id);
  ~Communication();

  void openCommunicationMain() override;
  void openCommunicationChild() override;
  void sendMsg(Package) override;
  Package receiveMsg(PackageType) override;
  void close() override;
  void rmfifo() override;
private:
  int _id;
  std::ofstream _outputPipe;
  std::ifstream _inputPipe;
};

#endif /* !COMMUNICATION_HPP_ */
