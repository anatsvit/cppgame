#ifndef PLAYER_H
#define PLAYER_H

#include "physic_entity.h"
#include "game.h"
#include <SFML/Graphics.hpp>

#define PLAYER_X_SPEED          1
#define PLAYER_WIDTH            16
#define PLAYER_HEIGHT           32
#define PLAYER_STATE_IDLE       0b00000000000000000000000000000001
#define PLAYER_STATE_MOVE_LEFT  0b00000000000000000000000000000010
#define PLAYER_STATE_MOVE_RIGHT 0b00000000000000000000000000000100
#define PLAYER_STATE_MOVE_DOWN  0b00000000000000000000000000001000
#define PLAYER_STATE_MOVE_UP    0b00000000000000000000000000010000

class Player: public PhysicEntity
{
    private:
        sf::RectangleShape shape;
        unsigned int state;
        float dx, dy;
        
        void checkKeyboard();

        void addState(int addedState);

        void removeState(int removedState);

        bool isState(int checkedState);
    public:
		void init();
		
		void update();

        void doState();

        void setX(float newX);
		
        void setY(float newY);
};

#endif
