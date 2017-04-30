#include "Ui.hpp"

#include <iostream>

Ui::Ui()
  : _width(1000), _height(1000)
{
}

Ui::~Ui()
{
}

void Ui::create()
{
  _window.create(sf::VideoMode(_width, _height), "plazza", sf::Style::Titlebar);
  _window.clear(sf::Color::Black);
  _modified = true;
}

void Ui::update(void)
{
  if (_modified)
    _window.display();
  _modified = false;
}

void Ui::drawRect(const size_t& x, const size_t& y, const size_t& width, const size_t& height, const sf::Color color, const bool& fill)
{
  sf::RectangleShape rect(sf::Vector2f(width, height));
  rect.setPosition(x, y);
  if (fill)
    rect.setFillColor(color);
  else
    {
      rect.setFillColor(sf::Color::Transparent);
      this->drawRect(x, y, width + 3, 1 + 3, color, true);
      this->drawRect(x, y + height - 1, width + 3, 1 + 3, color, true);
      this->drawRect(x, y, 1 + 3, height + 3, color, true);
      this->drawRect(x + width - 1, y, 1 + 3, height + 3, color, true);
    }
  _window.draw(rect);
  _modified = true;
}

void Ui::drawProcess()
{
  unsigned x = 0;
  unsigned y = 0;
  unsigned i = 0;
  unsigned nbSquare = _process.size();
  std::cout << nbSquare << std::endl;
  unsigned nbSquareLine = std::log2(nbSquare) + 2;
  unsigned squareSize = _width / (log2(nbSquare) + 2);
  std::cout << "Size : " << squareSize << std::endl;

  while (i < nbSquareLine && i < nbSquare)
    {
      drawRect(x + 10, y + 10, squareSize - 20, squareSize - 20, sf::Color::Blue);
      x += squareSize;
      i++;
    }
}

void Ui::setProcessList(std::vector<int> process)
{
  _process = process;
}
