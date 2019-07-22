#include "entity.h"

void Entity::setX(float newX)
{
    x = newX;
    tileX = ((int)(newX / 8));
}

void Entity::setY(float newY)
{
    y = newY;
    tileY = ((int)(newY / 8));
}

float Entity::getX()
{
    return x;
}

float Entity::getY()
{
    return y;
}

unsigned short Entity::getTileX(float shift)
{
    if (shift == 0) {
        return tileX;
    }
    
    return ((int)((this->getX() + shift) / 8));
}

unsigned short Entity::getTileY(float shift)
{
    if (shift == 0) {
        return tileY;
    }
    
    return ((int)((this->getY() + shift) / 8));
}

void Entity::init() {}

void Entity::update() {}

bool Entity::isCollision(Entity *e) 
{
    return false;
}

int Entity::getWidth()
{
    return 0;
}

int Entity::getHeight()
{
    return 0;
}

Entity::~Entity() {};
