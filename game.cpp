#include "game.h"
#include <SFML/Graphics.hpp>

sf::RenderWindow *Game::gameWindow;
Game *Game::game;

void Game::run()
{
	sf::RenderWindow window(sf::VideoMode(320,240), "Window");
	window.setFramerateLimit(60);
    Game::gameWindow = &window;
    
    this->currentMap = GameMap::loadFromFile("map_saved.bin");
    this->currentMap->init();
    
	while(window.isOpen()) {
		sf::Event event;
		while(window.pollEvent(event)) {
			if(event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		this->update();
		window.display();
	}
	
	delete this->currentMap;
}

void Game::update()
{
    this->currentMap->update();
}

GameMap* Game::getCurrentMap()
{
    return this->currentMap;
}  
