#include "Ui.hpp"

#include <iostream>

Ui::Ui(unsigned nbThread)
  : _width(1000), _height(1000), _nbThread(nbThread)
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

void Ui::drawRect(const unsigned& x, const unsigned& y, const size_t& width, const size_t& height, const sf::Color color, const bool& fill)
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
  unsigned j = 0;
  unsigned index = 0;
  unsigned nbSquare = _process.size();
  // std::cout << "nbSquare : " << nbSquare << std::endl;
  unsigned nbSquareLine = std::sqrt(nbSquare - 1) + 1;
  // unsigned nbSquareLine = std::log2(nbSquare - ((nbSquare == 1) ? 0 : 1)) + 2;
  unsigned squareSize = _width / (std::sqrt(nbSquare - 1) + 1);
  // std::cout << "nbSquareLine : " << nbSquareLine << std::endl;
  // std::cout << "Size : " << squareSize << std::endl << std::endl;

  while (j < nbSquareLine)
    {
      i = 0;
      x = 0;
      while (i < nbSquareLine && index < nbSquare)
	{
	  drawRect(x + 10, y + 10, squareSize - 20, squareSize - 20, sf::Color::Blue);
	  drawThreads(_process[index], x + 10, y + 10, squareSize - 20);
	  x += squareSize;
	  i++;
	  index++;
	}
      y += squareSize;
      j++;
    }
}

void Ui::drawThreads(const unsigned nbThreadUsed, const unsigned xP, const unsigned yP, const size_t sizeP)
{
  unsigned x = xP;
  unsigned y = yP;
  unsigned i = 0;
  unsigned j = 0;
  unsigned index = 0;
  unsigned nbSquare = _nbThread;
  std::cout << "SizeP : " << sizeP << std::endl;
  std::cout << "nbSquare : " << nbSquare << std::endl;
  unsigned nbSquareLine = std::sqrt(nbSquare - 1) + 1;
  unsigned squareSize = sizeP / (std::sqrt(nbSquare - 1) + 1);
  std::cout << "nbSquareLine : " << nbSquareLine << std::endl;
  std::cout << "Size : " << squareSize << std::endl << std::endl;

  while (j < nbSquareLine)
    {
      i = 0;
      x = xP;
      while (i < nbSquareLine && index < nbSquare)
	{
	  drawRect(x + 10, y + 10, squareSize - 20, squareSize - 20, (index < nbThreadUsed) ? sf::Color::Green : sf::Color::Red);
	  x += squareSize;
	  i++;
	  index++;
	}
      y += squareSize;
      j++;
    }
}

void Ui::setProcessList(std::vector<int> process)
{
  _process = process;
}
