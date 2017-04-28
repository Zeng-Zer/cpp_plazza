#include <iostream>
#include <regex>
#include <string>
#include <fstream>
#include <sstream>
#include "Scrapper.hpp"

Scrapper::Scrapper() {

}

Scrapper::~Scrapper() {

}

void  Scrapper::parseDocument(std::string const& file, Information info) {
  std::ifstream  myFile;
  std::smatch m;
  std::string myFileContent;
  std::regex	email("[-\\w.]+.[-\\w.]+@[-\\w.]+.[\\w]+");
  std::regex	ip("^((25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.){3}(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)$");
  std::regex	number("0[0-9](\\s[0-9][0-9]){4}|0[0-9]([0-9]){8}"); //le regex

  myFile.open(file);
  if(myFile.is_open())
  {
    while (getline(myFile, myFileContent))
    {
      if (info = IP_ADDRESS)
	{
	  if (std::regex_search (myFileContent,m,ip))
	    std::cout << "IP FOUND : " << m[0] << std::endl;
	}
      else if (info = EMAIL_ADDRESS)
	{
	  if (std::regex_search(myFileContent,m,email))
	    std::cout << "EMAIL FOUND : " << m[0] << std::endl;
	}
      else if (info = PHONE_NUMBER)
	{
	  if (std::regex_search(myFileContent,m,number))
	    std::cout << "NUMBER FOUND : " << m[0] << std::endl;
	}
    }
    myFile.close();
  }
}

int main(int ac, char **av)
{
  Scrapper  s;
  Scrapper::Information info = Scrapper::IP_ADDRESS;
  if (ac > 1)
    s.parseDocument(av[1], info);
  return 0;
}
