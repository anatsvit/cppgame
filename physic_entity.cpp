#include "physic_entity.h"

void PhysicEntity::setWidth(int newWidth)
{
    width = newWidth;
}

void PhysicEntity::setHeight(int newHeight)
{
    height = newHeight;
}

int PhysicEntity::getWidth()
{
    return width;
}

int PhysicEntity::getHeight()
{
    return height;
}

bool PhysicEntity::isCollision(PhysicEntity *other)
{
    return (this->getX() < (other->getX() + other->getWidth())) && 
           ((this->getX() + this->getWidth()) > other->getX()) && 
           (this->getY() < (other->getY() + other->getHeight())) && 
           ((this->getY() + this->getHeight()) > other->getY());      
}

