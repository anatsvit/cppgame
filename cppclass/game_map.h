#include <vector>
#include "entity.h"
#include "game_structs.h"
#include "entity_transformer.h"
#include "game.h"
#include "player.h"

#ifndef GAME_MAP_H
#define GAME_MAP_H
class GameMap
{
	private:
		std::vector<Entity*> entities;
        Entity *tiles[600][600]; 

        void levelEditor(int vector_size);

        void setTile(Entity *entity);

        void clearTile(int tileX, int tileY);

        void clearTiles();
    public:
        static GameMap* loadFromFile(const char *filename);
        		
		void init();
        
        void update();
		
		void addEntity(Entity* entity);

        Entity* getEntityByTile(unsigned short tileX, unsigned short tileY);

        ~GameMap();
};
#endif
