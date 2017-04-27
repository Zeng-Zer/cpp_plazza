#include "Task.hpp"
#include "Exception.hpp"

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
