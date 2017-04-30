#include <iostream>
#include <regex>
#include <string>
#include <fstream>
#include <sstream>
#include "Scrapper.hpp"
#include "Exception.hpp"
#include "Utils.hpp"

std::regex const Scrapper::_email("[a-zA-Z0-9_.-]+@[a-zA-Z0-9_.-]+");
std::regex const Scrapper::_ip("(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)(\\.(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)){3}");
std::regex const Scrapper::_number("0[0-9](\\s[0-9][0-9]){4}|0[0-9]([0-9]){8}");

std::map<Information, std::regex> const Scrapper::_regex = {
  {IP_ADDRESS, _ip},
  {EMAIL_ADDRESS, _email},
  {PHONE_NUMBER, _number},
};

Scrapper::Scrapper() {

}

Scrapper::~Scrapper() {

}

std::vector<std::string> Scrapper::caesar(std::string content, Information info) const {
  std::vector<std::string> res;
  for (int i = 0; i < 128; ++i) {
    for (auto &c : content) {
      c = (c + 1) % 128;
    }

    for (auto const& str : matchContent(content, info)) {
      res.push_back(str);
    }
  }

  return res;
}

std::vector<std::string> Scrapper::matchContent(std::string content, Information info) const {
  std::smatch m;

  std::vector<std::string> res;

  while (std::regex_search(content, m, _regex.at(info)) && res.size() < 6) {
    res.push_back(m[0]);
    if (info != IP_ADDRESS) {
      return res;
    }
    content = m.suffix().str();
  }

  return res;
}

std::vector<std::string> Scrapper::parseDocument(std::string const& file, Information info) const {
  if (Utils::isDirectory(file)) {
    throw FileException(file + " is a directory");
  }

  std::ifstream myFile(file);
  if (!myFile.is_open()) {
    throw FileException("File failed to open: " + file);
  }

  // initial content
  std::string content((std::istreambuf_iterator<char>(myFile)),
		      std::istreambuf_iterator<char>());

  std::vector<std::string> res = matchContent(content, info);
  if (info == IP_ADDRESS && res.empty()) {
    res = caesar(content, info);
  }

  return res;
}
