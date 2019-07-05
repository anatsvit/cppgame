#include <iostream>
#include <stdio.h>

using namespace std;

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
};

class PhysicEntity: public Entity 
{
      protected:
        float x;
        float y;
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

class GameMap
{
    public:
        static GameMap* loadFromFile(string filename)
        {
            //std::vector использовать для хранения наследников Entity

            //1.Открыть файл карты
            //2.Загрузить байты
            //3.Трансформировать байты в соответствующие объекты
            //4.Создать объект карты
            GameMap *gameMap = new GameMap;
            //5.Добавить к ней объекты
            
            //6.Вернуть объект карты  
            return gameMap;        
        }
        
        void update()
        {
            //1.Обход итератором по vector Entity, вызов у каждого update()
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
     
            //while (window->isOpen()) {
                this->update();
            //}      
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
