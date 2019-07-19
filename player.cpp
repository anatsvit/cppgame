#include "player.h"
#include <stdio.h>
#include <iostream>

void Player::checkKeyboard()
{    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        this->addState(PLAYER_STATE_MOVE_LEFT);
        this->removeState(PLAYER_STATE_MOVE_RIGHT);
        this->removeState(PLAYER_STATE_IDLE);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        this->addState(PLAYER_STATE_MOVE_RIGHT);
        this->removeState(PLAYER_STATE_MOVE_LEFT);
        this->removeState(PLAYER_STATE_IDLE);
    }
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && this->isState(PLAYER_STATE_IDLE)) {
        this->addState(PLAYER_STATE_JUMP);
        this->removeState(PLAYER_STATE_MOVE_DOWN);
        this->removeState(PLAYER_STATE_IDLE);
    }
}

void Player::addState(int addedState)
{
    this->state = this->state | addedState;
}

void Player::removeState(int removedState) 
{
    this->state = this->state & ~removedState;
}

bool Player::isState(int checkedState)
{
    return (this->state & checkedState) > 0;
}

void Player::init()
{
	sf::RectangleShape currentShape;
    currentShape.setSize(sf::Vector2f(PLAYER_WIDTH, PLAYER_HEIGHT));
    currentShape.setPosition(sf::Vector2f(this->getX(), this->getY()));
    currentShape.setFillColor(sf::Color::Cyan);
	this->shape = currentShape;
    this->addState(PLAYER_STATE_FALL);
}

void Player::update()
{
    Game::gameWindow->draw(this->shape);

	//1.Проверить нажатие клавиш
	this->checkKeyboard();
	//2.Проверить столкновение с другими физическими объектами на карте (проверять только тайлы вокруг персонажа)
   
	//3.Обновить координаты
	//4.Обновить скорость
	//5.Обновить состояние
	//6.Перерисовать
    this->doState();
}

void Player::doState()
{
    if (this->isState(PLAYER_STATE_IDLE)) {
        dx = 0;
        dy = 0;
    }  

    if (this->isState(PLAYER_STATE_MOVE_LEFT)) {
        dx = -PLAYER_X_SPEED;
        this->removeState(PLAYER_STATE_MOVE_LEFT);
        this->addState(PLAYER_STATE_IDLE);
    }

    if (this->isState(PLAYER_STATE_MOVE_RIGHT)) {
        dx = PLAYER_X_SPEED;
        this->removeState(PLAYER_STATE_MOVE_RIGHT);
        this->addState(PLAYER_STATE_IDLE);
    }
    
    this->addState(PLAYER_STATE_FALL);

    for (int i = 0; i < 3; i++) {
         if (Game::game->getCurrentMap()->getEntityByTile(this->getTileX() + i, this->getTileY() + 4)) {             
            this->removeState(PLAYER_STATE_FALL);
            this->addState(PLAYER_STATE_IDLE);
            break;
         }
    }

    if (this->isState(PLAYER_STATE_FALL)) {
        dy += 0.5;
        if (dy > 2) {
            dy = 2;        
        }        
    }

    if (this->isState(PLAYER_STATE_JUMP)) {
        dy = -4;
        this->removeState(PLAYER_STATE_JUMP);
    }

    this->setX(this->getX() + dx);
    this->setY(this->getY() + dy);
}

void Player::setX(float newX)
{
    Entity::setX(newX);
    this->shape.setPosition(sf::Vector2f(this->getX(), this->getY()));
    std::cout << "X:" << newX << std::endl;
}

void Player::setY(float newY)
{
    Entity::setY(newY);
    std::cout << "Y:" << newY << std::endl;
    this->shape.setPosition(sf::Vector2f(this->getX(), this->getY()));
}
