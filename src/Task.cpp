#include <string.h>
#include "Task.hpp"
#include "Exception.hpp"
#include "ICommunication.hpp"

std::map<std::string, Information> const Info::infos = {
  {"PHONE_NUMBER", PHONE_NUMBER},
  {"EMAIL_ADDRESS", EMAIL_ADDRESS},
  {"IP_ADDRESS", IP_ADDRESS}
};

Information Info::fromString(std::string const& str) {
  if (infos.count(str)) {
    return infos.at(str);
  }

  throw InformationException("Unrecognized information: " + str);
}

ICommunication& operator<<(ICommunication& c, const Package& msg)
{
  c.sendMsg(msg);
  return c;
}

ICommunication& operator>>(ICommunication& c, Package& msg)
{
  msg = c.receiveMsg();
  return c;
}
