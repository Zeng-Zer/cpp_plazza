#include "Communication.hpp"

Communication::Communication(int id)
  : _id(id)
{
  rmfifo();
}

Communication::~Communication()
{
}

void Communication::openCommunicationMain()
{
  std::string oPath(PFIFO + std::to_string(_id));
  std::string iPath(PFIFO + std::to_string(_id + 1));

  int fifo = mkfifo(oPath.c_str(), S_IRWXU);
  if (fifo == -1)
    throw CommunicationException("Parent: Error while creating named pipe");
  fifo = mkfifo(iPath.c_str(), 0666);
  if (fifo == -1)
    throw CommunicationException("Parent: Error while create named pipe");

  _fdOutputPipe = open(oPath.c_str(), O_RDWR | O_CREAT | O_NONBLOCK);
  if (_fdOutputPipe == -1)
    throw CommunicationException("Parent: Error while opening output named pipe");
  _fdInputPipe = open(iPath.c_str(), O_RDWR | O_CREAT | O_NONBLOCK);
  if (_fdInputPipe == -1)
    throw CommunicationException("Parent: Error while opening input named pipe");
}

void Communication::openCommunicationChild()
{
  std::string oPath(PFIFO + std::to_string(_id + 1));
  std::string iPath(PFIFO + std::to_string(_id));

  _fdInputPipe = open(iPath.c_str(), O_RDWR | O_CREAT | O_NONBLOCK);
  if (_fdInputPipe == -1)
    throw CommunicationException("Child: Error while opening input named pipe");
  _fdOutputPipe = open(oPath.c_str(), O_RDWR | O_CREAT | O_NONBLOCK);
  if (_fdOutputPipe == -1)
    throw CommunicationException("Child: Error while opening output named pipe");
}

void Communication::sendMsg(Package msg)
{
  write(_fdOutputPipe, reinterpret_cast<char*>(&msg), sizeof(Package));
}

Package Communication::receiveMsg()
{
  Package msg;
  int r;

  r = read(_fdInputPipe, reinterpret_cast<char*>(&msg), sizeof(Package));
  msg.type = UNDEFINED;
  if (r == 0)
    {
      msg.content.value = -1;
    }
  return (msg);
}

void Communication::close()
{
  ::close(_fdOutputPipe);
  ::close(_fdInputPipe);
}

void Communication::rmfifo()
{
  std::string oPath(PFIFO + std::to_string(_id + 1));
  std::string iPath(PFIFO + std::to_string(_id));

  unlink(oPath.c_str());
  unlink(iPath.c_str());
}
