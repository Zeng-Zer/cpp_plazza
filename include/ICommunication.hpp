#ifndef ICOMMUNICATION_HPP_
# define ICOMMUNICATION_HPP_

#include "Task.hpp"

/**
 * interface to sockets/pipe
 */
class ICommunication {
public:
  virtual ~ICommunication() {}

  /**
   * Open main communication
   */
  virtual void openCommunicationMain() = 0;

  /**
   * Open child communication
   */
  virtual void openCommunicationChild() = 0;

  /**
   * send a msg
   */
  virtual void sendMsg(Package) = 0;

  /**
   * rcv a msg
   */
  virtual Package receiveMsg() = 0;

  /**
   * close the communication
   */
  virtual void close() = 0;

  /**
   * clean fifo
   */
  virtual void rmfifo() = 0;
};

#endif /* !ICOMMUNICATION_HPP_ */
