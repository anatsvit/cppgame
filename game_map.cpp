#include "game_map.h"
#include <SFML/Graphics.hpp>

sf::RenderWindow *Game::gameWindow;

void GameMap::levelEditor(int vector_size) 
{
    //Create platform block
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        EntityPlace *entityPlace = new EntityPlace;
        entityPlace->x_coor = ((int)(sf::Mouse::getPosition(*Game::gameWindow).x / 8)) * 8;
        entityPlace->y_coor = ((int)(sf::Mouse::getPosition(*Game::gameWindow).y / 8)) * 8;
        entityPlace->type = ENTITY_TYPE_PLATFORM;
        bool exists = false;
        
        for (int i = 0; i < vector_size; i++) {
		    if (this->entities[i]->getX() == entityPlace->x_coor && this->entities[i]->getY() == entityPlace->y_coor) {
                exists = true;
                break;                
            }
	    }
        
        if (!exists && entityPlace->x_coor % 8 == 0 && entityPlace->y_coor % 8 == 0) {
            Entity *entity = EntityTransformer::transform(entityPlace);
            
            entity->init();
            this->addEntity(entity);
        }
        
        delete entityPlace;
    }
    
    //Remove platform block
    if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
        int tileX = ((int)(sf::Mouse::getPosition(*Game::gameWindow).x / 8)) * 8;
        int tileY = ((int)(sf::Mouse::getPosition(*Game::gameWindow).y / 8)) * 8;

        for (int i = 0; i < vector_size; i++) {
              if (this->entities[i]->getX() == tileX && this->entities[i]->getY() == tileY) { 
                    delete this->entities[i];
                    this->entities.erase(this->entities.begin() + i);
              }              
        }
    } 

    if (sf::Mouse::isButtonPressed(sf::Mouse::Middle)) {
        FILE *mapfile = fopen("map_saved.bin", "wb"); 
        unsigned short buffer[3];
        for (int i = 0; i < vector_size; i++) {
		    buffer[0] = this->entities[i]->getX();
            buffer[1] = this->entities[i]->getY();
            buffer[2] = ENTITY_TYPE_PLATFORM;
            fwrite(buffer, 6, 1, mapfile);
	    }

        fclose(mapfile);          
    }    
}

void GameMap::setTile(Entity *entity)
{
    //cout << "XSET: " << entity->getTileX() << endl;
    //cout << "YSET: " << entity->getTileY() << endl;
    this->tiles[entity->getTileX()][entity->getTileY()] = entity;
}

void GameMap::clearTile(int tileX, int tileY)
{
    this->tiles[tileX][tileY] = nullptr;  
}

void GameMap::clearTiles()
{
    for (int i = 0; i < 600; i++) {
        for (int j = 0; j < 600; j++) {
            this->tiles[i][j] = nullptr;             
        }
    }   
}

GameMap* GameMap::loadFromFile(const char *filename)
{
	GameMap *gameMap = new GameMap;
    //1.Открыть файл (filename) карты
	FILE *mapfile = fopen(filename, "rb");
	EntityPlace *entityPlace = new EntityPlace;

	//2.Загрузить байты
    while (!feof(mapfile)) {
	    fread(entityPlace, 6, 1, mapfile);
	    
	    if (feof(mapfile)) {
		    break;
	    }
	    
	    gameMap->addEntity(EntityTransformer::transform(entityPlace));
    }
	
	delete entityPlace;
	fclose(mapfile);
    
    return gameMap;        
}

void GameMap::init()
{
    this->clearTiles();
    
    Player *player = new Player();
    player->setX(32);
    player->setY(32);
    this->addEntity(player);
	unsigned int vector_size = this->entities.size();
	
	for (int i = 0; i < vector_size; i++) {
		this->entities[i]->init();
	}
    
    /*for (int i = 0; i < 8; i++) {
        cout << this->getEntityByTile(i, i) << endl;   
    }   */ 
}

void GameMap::update()
{
    unsigned int vector_size = this->entities.size();
	
	for (int i = 0; i < vector_size; i++) {
		this->entities[i]->update();
	}

    this->levelEditor(vector_size);
}

void GameMap::addEntity(Entity* entity)
{
	this->entities.push_back(entity);
    this->setTile(entity);
}

Entity* GameMap::getEntityByTile(unsigned short tileX, unsigned short tileY)
{
    return this->tiles[tileX][tileY];
}

GameMap::~GameMap()
{
    unsigned int vector_size = this->entities.size();
    for (int i = 0; i < vector_size; i++) {
        delete this->entities[i];       
    }
}
