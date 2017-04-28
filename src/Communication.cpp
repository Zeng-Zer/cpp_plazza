#include "Communication.hpp"

Communication::Communication(int id)
  :_outputId(id % 2), _inputId(id % 2)
{
}

Communication::~Communication()
{
}

void Communication::openCommunication()
{
  std::string oPath(PFIFO + std::to_string(_outputId));
  std::string iPath(PFIFO + std::to_string(_inputId));

  int fifo = mkfifo(oPath.c_str(), 0666);
  if (fifo == -1)
    throw CommunicationException("Error on create named pipe");
  _outputPipe.open(oPath, std::ofstream::out | std::ofstream::binary);
  if (!_outputPipe.is_open())
    throw CommunicationException("Error on open output named pipe");
  // _inputPipe.open(iPath, std::ifstream::in | std::ifstream::binary);
}

void Communication::sendMsg() const
{

}
