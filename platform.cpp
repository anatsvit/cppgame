#include "platform.h"

void Platform::init()
{
    sf::RectangleShape currentShape;
    currentShape.setSize(sf::Vector2f(8, 8));
    currentShape.setPosition(sf::Vector2f(this->getX(), this->getY()));
    currentShape.setFillColor(sf::Color::Red);
	this->shape = currentShape;
}

void Platform::update()
{
	Game::gameWindow->draw(this->shape);
}
