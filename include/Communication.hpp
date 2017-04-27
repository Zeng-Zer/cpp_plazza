#ifndef COMMUNICATION_HPP_
# define COMMUNICATION_HPP_

#include <string>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include "ICommunication.hpp"

class Communication : public ICommunication
{
public:
  Communication(int id);
  ~Communication();

  void openCommunication();
private:
  int _id;
  int _fifo;
  int _fd;
};

#endif /* !COMMUNICATION_HPP_ */
