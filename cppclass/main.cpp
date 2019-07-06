#include <iostream>
#include <stdio.h>
#include <vector>
#include <SFML/Graphics.hpp>

#define ENTITY_TYPE_PLATFORM 1

using namespace std;
using namespace sf;

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
    public:
		void init()
		{
			//1.Загрузить и установить спрайт
			cout << "INIT X: " << this->getX() << endl;
			cout << "INIT Y: " << this->getY() << endl;
		}
		
		void update()
		{
			//6.Перерисовать
			cout << "UPD X: " << this->getX() << endl;
			cout << "UPD Y: " << this->getY() << endl;
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
        }
		
		void addEntity(Entity* entity)
		{
			this->entities.push_back(entity);
		}
};

class Game
{
    private: 
        //Window *window;
        GameMap *map;
    
    public: 
        void run()
        {
            this->map = GameMap::loadFromFile("map01.bin");
			this->map->init();
			RenderWindow window(VideoMode(320,240), "Window");
			window.setFramerateLimit(60);

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
    
    return 0;
}
