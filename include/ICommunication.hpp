#ifndef ICOMMUNICATION_HPP_
# define ICOMMUNICATION_HPP_

/**
 * interface to sockets/pipe
 */
class ICommunication {
public:
  virtual ~ICommunication() {}

  // TODO Method to communicate between plazza and process

  virtual int openCommunication() = 0; // TODO TBD PARAMETER

  /**
   * send a msg
   */
  virtual void sendMsg() const = 0; // TODO TBD PARAMETER

  /**
   * rcv a msg
   */
  virtual void receiveMsg() const = 0; // TODO TBD PARAMETER

  /**
   * close the communication
   */
  virtual void close() = 0;
};

#endif /* !ICOMMUNICATION_HPP_ */
