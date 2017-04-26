#ifndef SCRAPPER_HPP_
# define SCRAPPER_HPP_

# include <string>
# include <vector>
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
  std::vector<std::string> parseDocument(std::string const& file, Information info);

private:

};

#endif /* !SCRAPPER_HPP_ */
