#ifndef ICOMMUNICATION_HPP_
# define ICOMMUNICATION_HPP_

class ICommunication {
public:
  virtual ~ICommunication() {}

  // TODO Method to communicate between plazza and process

  virtual int openCommunication(); // TODO TBD PARAMETER

  /**
   * send a msg
   */
  virtual void sendMsg() const = 0; // TODO TBD PARAMETER

  /**
   * rcv a msg
   */
  virtual void receiveMsg() const = 0; // TODO TBD PARAMETER
};

#endif /* !ICOMMUNICATION_HPP_ */
