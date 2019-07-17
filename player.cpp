#include "player.h"
#include <stdio.h>
#include <iostream>

void Player::checkKeyboard()
{
    this->removeState(PLAYER_STATE_MOVE_RIGHT);
    this->removeState(PLAYER_STATE_MOVE_LEFT);
    this->removeState(PLAYER_STATE_MOVE_DOWN);
    this->removeState(PLAYER_STATE_MOVE_UP);
    this->addState(PLAYER_STATE_IDLE);            
    
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
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        this->addState(PLAYER_STATE_MOVE_UP);
        this->removeState(PLAYER_STATE_MOVE_DOWN);
        this->removeState(PLAYER_STATE_IDLE);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        this->addState(PLAYER_STATE_MOVE_DOWN);
        this->removeState(PLAYER_STATE_MOVE_UP);
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
    this->addState(PLAYER_STATE_IDLE);
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
    if (this->isState(PLAYER_STATE_MOVE_LEFT)) {
        dx = -PLAYER_X_SPEED;

        for (int i = 0; i < 5; i++) {
            if (Game::game->getCurrentMap()->getEntityByTile(this->getTileX(), this->getTileY() + i)) {
                this->removeState(PLAYER_STATE_MOVE_LEFT);
                this->addState(PLAYER_STATE_IDLE);
                break;
            }        
        }
    }

    if (this->isState(PLAYER_STATE_MOVE_RIGHT)) {
        dx = PLAYER_X_SPEED;
        
        for (int i = 0; i < 5; i++) {
            if (Game::game->getCurrentMap()->getEntityByTile(this->getTileX() + 2, this->getTileY() + i)) {
                this->removeState(PLAYER_STATE_MOVE_RIGHT);
                this->addState(PLAYER_STATE_IDLE);
                break;
            }        
        }
    }

    if (this->isState(PLAYER_STATE_MOVE_UP)) {
        dy = -PLAYER_X_SPEED;
    }

    if (this->isState(PLAYER_STATE_MOVE_DOWN)) {
        dy = PLAYER_X_SPEED;
        
        for (int i = 0; i < 3; i++) {
             if (Game::game->getCurrentMap()->getEntityByTile(this->getTileX() + i, this->getTileY(0.9) + 4)) {             
                this->removeState(PLAYER_STATE_MOVE_DOWN);
                this->addState(PLAYER_STATE_IDLE);
                break;
             }
        }
    }

    if (this->isState(PLAYER_STATE_IDLE)) {
        dx = 0;
        dy = 0;
    }

    this->setX(this->getX() + dx);
    this->setY(this->getY() + dy);
}

void Player::setX(float newX)
{
    Entity::setX(newX);
    this->shape.setPosition(sf::Vector2f(this->getX(), this->getY()));
}

void Player::setY(float newY)
{
    Entity::setY(newY);
    this->shape.setPosition(sf::Vector2f(this->getX(), this->getY()));
}
