class Game
{
    private Window window;
    private Map map;
    
    public function run()
    {
        Map map = Map::loadFromFile('map01.bin');
 
        while (window.isOpen()) {
            this.update();
        }      
    }

    public function update()
    {
        map.update();   
    }    
}
