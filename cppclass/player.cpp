#include "player.h"

void Player::checkKeyboard()
{
    this->removeState(PLAYER_STATE_MOVE_RIGHT);
    this->removeState(PLAYER_STATE_MOVE_LEFT);
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
    if (this->isState(PLAYER_STATE_IDLE)) {
        dx = 0;
    }

    if (this->isState(PLAYER_STATE_MOVE_LEFT)) {
        dx = -PLAYER_X_SPEED;
        //cout << "TILE_X: " << this->getTileX() << endl; 
        /*for (int i = 0; i < 3; i++) {
            cout << game->getCurrentMap() << endl;
        }*/
    }

    if (this->isState(PLAYER_STATE_MOVE_RIGHT)) {
        dx = PLAYER_X_SPEED;
        //cout << "TILE_X: " << this->getTileX() << endl;
    }

    this->setX(this->getX() + dx);
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
