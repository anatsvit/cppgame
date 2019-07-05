#include "entity.h"

class PhysicEntity: public Entity 
{
      protected:
        float x;
        float y;
        int width;
        int height;

      public:
        void setWidth(int newWidth)
        {
            width = newWidth;
        }

        void setHeight(int newHeight)
        {
            height = newHeight;
        }
        
        int getWidth()
        {
            return width;
        }

        int getHeight()
        {
            return height;
        }

        bool isCollision(PhysicEntity *other)
        {
            return (this->getX() < (other->getX() + other->getWidth())) && 
                   ((this->getX() + this->getWidth()) > other->getX()) && 
                   (this->getY() < (other->getY() + other->getHeight())) && 
                   ((this->getY() + this->getHeight()) > other->getY());      
        }
};
