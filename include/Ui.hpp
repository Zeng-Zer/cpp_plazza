#ifndef UI_HPP_
# define UI_HPP_

# include <cmath>
# include <SFML/Graphics.hpp>

class Ui
{
public:
  Ui();
  ~Ui();

  void create();
  void update(void);

  void drawRect(const size_t& x, const size_t& y, const size_t& width, const size_t& height, const sf::Color color, const bool& fill = true);
  void drawProcess();

  void setProcessList(std::vector<int> process);

private:
  unsigned _width;
  unsigned _height;
  std::vector<int> _process;
  sf::RenderWindow _window;
  bool _modified;

};

#endif /* !UI_HPP_ */
