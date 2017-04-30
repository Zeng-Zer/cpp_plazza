#include <iostream>
#include <regex>
#include <string>
#include <fstream>
#include <sstream>
#include "Scrapper.hpp"
#include "Exception.hpp"
#include "Utils.hpp"

Scrapper::Scrapper() {

}

Scrapper::~Scrapper() {

}

std::string Scrapper::parseDocument(std::string const& file, Information info) const {
  std::smatch m;
  std::regex email("[a-zA-Z0-9_.-]+@[a-zA-Z0-9_.-]+");
  std::regex ip("(([0-9]|[1-9][0-9]|1[0-9]{2}|2[0-4][0-9]|25[0-5])\\.){3}([0-9]|[1-9][0-9]|1[0-9]{2}|2[0-4][0-9]|25[0-5])");
  std::regex number("0[0-9](\\s[0-9][0-9]){4}|0[0-9]([0-9]){8}");

  if (Utils::isDirectory(file)) {
    throw FileException(file + " is a directory");
  }

  std::ifstream myFile(file, std::ifstream::binary);
  if (!myFile.is_open()) {
    throw FileException("File failed to open: " + file);
  }

  std::string content((std::istreambuf_iterator<char>(myFile)),
		      std::istreambuf_iterator<char>());

  switch (info) {
  case IP_ADDRESS:
    if (std::regex_search(content, m, ip)) {
      return m[0];
    }

  case EMAIL_ADDRESS:
    if (std::regex_search(content, m, email)) {
      return m[0];
    }

  case PHONE_NUMBER:
    if (std::regex_search(content, m, number)) {
      return m[0];
    }
  }

  return "";
}
