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
    
    public:
        void setX(float newX)
        {
            x = newX;
        }

        void setY(float newY)
        {
            y = newY;
        }
        
        float getX()
        {
            return x;
        }

        float getY()
        {
            return y;
        }
		
		virtual void init() {}
    
		virtual void update() {}
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
    public:
		void init()
		{
			//1.Загрузить и установить спрайт
		}
		
		void update()
		{
			//1.Проверить нажатие клавиш
			this->checkKeyboard();
			//2.Проверить столкновение с другими физическими объектами на карте (проверять только тайлы вокруг персонажа)
			//3.Обновить координаты
			//4.Обновить скорость
			//5.Обновить состояние
			//6.Перерисовать
		}

	private:
		void checkKeyboard()
		{
			//1.Проверка нажатия клавиши
			//2.Реакция на клавишу (смена состояния)
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
			unsigned int vector_size = this->entities.size();
			
			for (int i = 0; i < vector_size; i++) {
				this->entities[i]->init();
			}
        }
        
        void update()
        {
            unsigned int vector_size = this->entities.size();
			
			for (int i = 0; i < vector_size; i++) {
				this->entities[i]->update();
			}

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
        }
		
		void addEntity(Entity* entity)
		{
			this->entities.push_back(entity);
		}
};

class Game
{
    private: 
        GameMap *map;
    
    public: 
        void run()
        {
            this->map = GameMap::loadFromFile("map01.bin");
			
			RenderWindow window(VideoMode(320,240), "Window");
			window.setFramerateLimit(60);
            gameWindow = &window;
            this->map->init();

			while(window.isOpen()) {
				Event event;
				while(window.pollEvent(event))
				{
					if(event.type == Event::Closed)
						window.close();
				}

				window.clear();
				this->update();
				window.display();
			}  
			
			delete this->map;
        }

        void update()
        {
            this->map->update();   
        }    
};

int main()
{
    Game *game = new Game();
    game->run();

    delete game;
    
    return 0;
}
