#ifndef ENTITY_H
#define ENTITY_H

#define ENTITY_TYPE_PLATFORM 1

class Entity 
{
    protected:
        float x;
        float y;
        unsigned short tileX;
        unsigned short tileY;
    
    public:
        virtual void setX(float newX);

        virtual void setY(float newY);
        
        float getX();

        float getY();

        unsigned short getTileX();

        unsigned short getTileY();
		
		virtual void init();
    
		virtual void update();
        
        virtual ~Entity();
};

#endif
