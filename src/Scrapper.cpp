#include <iostream>
#include <regex>
#include <string>
#include <fstream>
#include <sstream>
#include "Scrapper.hpp"
#include "Exception.hpp"

Scrapper::Scrapper() {

}

Scrapper::~Scrapper() {

}

std::vector<std::string>  Scrapper::parseDocument(std::string const& file, Information info) {
  std::smatch m;
  std::string myFileContent;
  std::regex email("[-\\w.]+.[-\\w.]+@[-\\w.]+.[\\w]+");
  std::regex ip("^((25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.){3}(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)$");
  std::regex number("0[0-9](\\s[0-9][0-9]){4}|0[0-9]([0-9]){8}");

  std::ifstream myFile(file);
  if (!myFile.is_open()) {
    throw FileException("File failed to open: " + file);
  }

  std::vector<std::string> result;
  while (getline(myFile, myFileContent)) {

    switch (info) {

    case IP_ADDRESS:
      if (std::regex_search(myFileContent, m, ip)) {
	result.push_back(m[0]);
      }
      break;

    case EMAIL_ADDRESS:
      if (std::regex_search(myFileContent, m, email)) {
	result.push_back(m[0]);
      }
      break;

    case PHONE_NUMBER:
      if (std::regex_search(myFileContent, m, number)) {
	result.push_back(m[0]);
      }
      break;

    }

  }
  myFile.close();
  return result;
}
