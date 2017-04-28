#ifndef ICOMMUNICATION_HPP_
# define ICOMMUNICATION_HPP_

#include "Task.hpp"

/**
 * interface to sockets/pipe
 */
class ICommunication {
public:
  virtual ~ICommunication() {}

  // TODO Method to communicate between plazza and process

  virtual void openCommunicationMain() = 0;
  virtual void openCommunicationChild() = 0;

  /**
   * send a msg
   */
  virtual void sendMsg(Package) = 0;

  /**
   * rcv a msg
   */
  virtual Package receiveMsg(PackageType) = 0;

  /**
   * close the communication
   */
  virtual void close() = 0;
  virtual void rmfifo() = 0;
};

#endif /* !ICOMMUNICATION_HPP_ */
