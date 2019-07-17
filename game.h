#ifndef GAME_H
#define GAME_H
#include "game_map.h"
#include <SFML/Graphics.hpp>
class GameMap;
class Game
{
    private:
        GameMap *currentMap;
    public: 
        static sf::RenderWindow *gameWindow;
        static Game *game;
        void run();
        void update(); 
        GameMap* getCurrentMap();
};
#endif
