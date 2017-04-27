#include "Communication.hpp"

Communication::Communication(int id)
  :_id(id)
{
  
}

Communication::~Communication()
{
  
}

int Communication::openCommunication()
{
  std::string str_fifo("/tmp/plazza" + std::to_string(_id));
  _fifo = mkfifo(str_fifo.c_str(), 0666);
  _fd = open(str_fifo.c_str(), O_WRONLY);
}
