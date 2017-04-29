#ifndef UI_HPP_
# define UI_HPP_

# include <SFML/Graphics.hpp>

class Ui
{
public:
  Ui();
  ~Ui();

  void create();
  void update(void);

private:
  sf::RenderWindow _window;
  bool _modified;

};

#endif /* !UI_HPP_ */
