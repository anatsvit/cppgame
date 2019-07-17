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

unsigned short Entity::getTileX()
{
    return tileX;
}

unsigned short Entity::getTileY()
{
    return tileY;
}

void Entity::init() {}

void Entity::update() {}

Entity::~Entity() {};
