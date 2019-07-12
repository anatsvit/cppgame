#include <iostream>
#include <stdio.h>
#include <vector>
#include <SFML/Graphics.hpp>

#define ENTITY_TYPE_PLATFORM 1

using namespace std;
using namespace sf;

RenderWindow *gameWindow;

class Entity 
{
    protected:
        float x;
        float y;
        unsigned short tileX;
        unsigned short tileY;
    
    public:
        virtual void setX(float newX)
        {
            x = newX;
            tileX = ((int)(newX / 8));
        }

        virtual void setY(float newY)
        {
            y = newY;
            tileY = ((int)(newY / 8));
        }
        
        float getX()
        {
            return x;
        }

        float getY()
        {
            return y;
        }

        unsigned short getTileX()
        {
            return tileX;
        }

        unsigned short getTileY()
        {
            return tileY;
        }
		
		virtual void init() {}
    
		virtual void update() {}
        
        virtual ~Entity() {};
};

class PhysicEntity: public Entity 
{
      protected:
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

class Player: public PhysicEntity
{
    private:
        RectangleShape shape;
        
        void checkKeyboard()
		{
			//1.Проверка нажатия клавиши
			//2.Реакция на клавишу (смена состояния)
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                this->setX(this->getX() - 0.4);
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                 this->setX(this->getX() + 0.4);
            }
		}
    public:
		void init()
		{
			RectangleShape currentShape;
            currentShape.setSize(Vector2f(16, 32));
            currentShape.setPosition(Vector2f(this->getX(), this->getY()));
            currentShape.setFillColor(Color::Cyan);
			this->shape = currentShape;
		}
		
		void update()
		{
            gameWindow->draw(this->shape);

			//1.Проверить нажатие клавиш
			this->checkKeyboard();
			//2.Проверить столкновение с другими физическими объектами на карте (проверять только тайлы вокруг персонажа)
			//3.Обновить координаты
			//4.Обновить скорость
			//5.Обновить состояние
			//6.Перерисовать
		}

        void setX(float newX)
        {
            Entity::setX(newX);
            this->shape.setPosition(Vector2f(this->getX(), this->getY()));
        }
		
        void setY(float newY)
        {
            Entity::setY(newY);
            this->shape.setPosition(Vector2f(this->getX(), this->getY()));
        }
};

class Platform: public PhysicEntity
{
    private:
        RectangleShape shape;
    public:
		void init()
		{
            RectangleShape currentShape;
            currentShape.setSize(Vector2f(8, 8));
            currentShape.setPosition(Vector2f(this->getX(), this->getY()));
            currentShape.setFillColor(Color::Red);
			this->shape = currentShape;
		}
		
		void update()
		{
			gameWindow->draw(this->shape);
		}
};

struct EntityPlace
{ 
	unsigned short x_coor; 
	unsigned short y_coor; 
	unsigned short type;
};

class EntityTransformer
{
	public:
		static Entity* transform(EntityPlace *eplace)
		{
			if (eplace->type == ENTITY_TYPE_PLATFORM) {
				Platform *platform = new Platform();
				platform->setX(eplace->x_coor);
				platform->setY(eplace->y_coor);
				return platform;
			}
			
			return new Entity();
		}
};

class GameMap
{
	private:
		vector<Entity*> entities;
        Entity *tiles[600][600]; 

        void levelEditor(int vector_size) 
        {
            //Create platform block
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                EntityPlace *entityPlace = new EntityPlace;
                entityPlace->x_coor = ((int)(sf::Mouse::getPosition(*gameWindow).x / 8)) * 8;
                entityPlace->y_coor = ((int)(sf::Mouse::getPosition(*gameWindow).y / 8)) * 8;
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
                int tileX = ((int)(sf::Mouse::getPosition(*gameWindow).x / 8)) * 8;
                int tileY = ((int)(sf::Mouse::getPosition(*gameWindow).y / 8)) * 8;

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

        void setTile(Entity *entity)
        {
            cout << "XSET: " << entity->getTileX() << endl;
            cout << "YSET: " << entity->getTileY() << endl;
            this->tiles[entity->getTileX()][entity->getTileY()] = entity;
        }

        void clearTile(int tileX, int tileY)
        {
            this->tiles[tileX][tileY] = nullptr;  
        }

        void clearTiles()
        {
            for (int i = 0; i < 600; i++) {
                for (int j = 0; j < 600; j++) {
                    this->tiles[i][j] = nullptr;             
                }
            }   
        }
    public:
        static GameMap* loadFromFile(const char *filename)
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
		
		void init()
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
            
            for (int i = 0; i < 8; i++) {
                cout << this->getEntityByTile(i, i) << endl;   
            }    
        }
        
        void update()
        {
            unsigned int vector_size = this->entities.size();
			
			for (int i = 0; i < vector_size; i++) {
				this->entities[i]->update();
			}

            this->levelEditor(vector_size);
        }

        
		
		void addEntity(Entity* entity)
		{
			this->entities.push_back(entity);
            this->setTile(entity);
		}

        Entity* getEntityByTile(unsigned short tileX, unsigned short tileY)
        {
            return this->tiles[tileX][tileY];
        }

        ~GameMap()
        {
            unsigned int vector_size = this->entities.size();
            for (int i = 0; i < vector_size; i++) {
                delete this->entities[i];       
            }
        }
};

class Game
{
    public: 
        void run()
        {
			RenderWindow window(VideoMode(320,240), "Window");
			window.setFramerateLimit(60);
            gameWindow = &window;
            
            
            GameMap *map = GameMap::loadFromFile("map_saved.bin");
            map->init();
            
			while(window.isOpen()) {
				Event event;
				while(window.pollEvent(event)) {
					if(event.type == Event::Closed)
						window.close();
				}

				window.clear();
				this->update(map);
				window.display();
			}
			
			delete map;
        }

        void update(GameMap *map)
        {
            map->update();   
        }    
};

int main()
{
    Game *game = new Game();
    game->run();

    delete game;
    
    return 0;
}
