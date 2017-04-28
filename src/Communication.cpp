#include "Communication.hpp"

Communication::Communication(int id)
{
  if (id % 2)
    {
      _outputId = id;
      _inputId = id++;
    }
  else
    {
      _outputId = id;
      _inputId = id++;
    }
}

Communication::~Communication()
{
}

void Communication::openCommunicationMain()
{
  std::string oPath(PFIFO + std::to_string(_outputId));
  std::string iPath(PFIFO + std::to_string(_inputId));

  int fifo = mkfifo(oPath.c_str(), 0666);
  if (fifo == -1)
    throw CommunicationException("Error on create named pipe");
  fifo = mkfifo(iPath.c_str(), 0666);
  if (fifo == -1)
    throw CommunicationException("Error on create named pipe");
  _outputPipe.open(oPath, std::ofstream::out | std::ofstream::binary);
  if (!_outputPipe.is_open())
    throw CommunicationException("Error on open output named pipe");
  // _inputPipe.open(iPath, std::ifstream::in | std::ifstream::binary);
}

void Communication::openCommunicationChild()
{
  
}

void Communication::sendMsg(Package& msg)
{
  _outputPipe.write(reinterpret_cast<char*>(&msg), sizeof(Package));
}

Package& Communication::receiveMsg()
{
  Package *msg = new Package;
  _inputPipe.read(reinterpret_cast<char*>(msg), sizeof(Package));
  return (*msg);
}

void Communication::close()
{
  _outputPipe.close();
  _inputPipe.close();
}
