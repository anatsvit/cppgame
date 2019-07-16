#ifndef PLATFORM_H
#define PLATFORM_H
#include "physic_entity.h"
#include "game.h"
#include <SFML/Graphics.hpp>

class Platform: public PhysicEntity
{
    private:
        sf::RectangleShape shape;
    public:
		void init();
		
		void update();
};
#endif
