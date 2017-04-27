#ifndef EXCEPTION_HPP_
# define EXCEPTION_HPP_

# include <exception>
# include <string>

class Exception : public std::exception {
public:
  Exception(std::string const& msg);
  virtual ~Exception();

  char const *what() const throw();

private:
  std::string _msg;
};

/**
 * bad information from stdin
 */
class InformationException : public Exception {
public:
  InformationException(std::string const& msg);
};

/**
 * fork failure
 */
class ProcessException : public Exception {
public:
  ProcessException(std::string const& msg);
};

/**
 * communication failure
 */
class CommunicationException : public Exception {
public:
  CommunicationException(std::string const& msg);
};

#endif /* !EXCEPTION_HPP_ */
