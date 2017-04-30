#ifndef SCRAPPER_HPP_
# define SCRAPPER_HPP_

# include <string>
# include <vector>
# include <regex>
# include "Task.hpp"

/**
 * Scrape web pages to retrieve an information
 * Parsing
 */
class Scrapper {
public:
  Scrapper();
  ~Scrapper();

  /**
   * parse a file to retrieve data
   */
  std::vector<std::string> parseDocument(std::string const& file, Information info) const;

  /**
   * match content with corresponding regex
   */
  std::vector<std::string> matchContent(std::string content, Information info) const;

  /**
   * decifer caesar
   */
  std::vector<std::string> caesar(std::string content, Information info) const;

private:
  static std::regex const _email;
  static std::regex const _ip;
  static std::regex const _number;
  static std::map<Information, std::regex> const _regex;
};

#endif /* !SCRAPPER_HPP_ */
