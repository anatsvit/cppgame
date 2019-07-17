#include <iostream>
#include <stdio.h>
#include "game.h"

int main()
{
    Game::game = new Game();
    Game::game->run();

    delete Game::game;
    
    return 0;
}
