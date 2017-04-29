#include "Ui.hpp"

#include <iostream>

Ui::Ui()
{
}

Ui::~Ui()
{
}

void Ui::create()
{
  _window.create(sf::VideoMode(800, 600), "plazza", sf::Style::None);
  _window.clear(sf::Color::Black);
  _modified = true;
  std::cout << "yoloswag" << std::endl;
}

void Ui::update(void)
{
  if (_modified)
    _window.display();
  _modified = false;
}
