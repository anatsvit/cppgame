#ifndef PHYSIC_ENTITY_H
#define PHYSIC_ENTITY_H
#include "entity.h"

class PhysicEntity: public Entity 
{
      protected:
        int width;
        int height;

      public:
        void setWidth(int newWidth);

        void setHeight(int newHeight);
        
        int getWidth();

        int getHeight();

        bool isCollision(Entity *other);
};

#endif
