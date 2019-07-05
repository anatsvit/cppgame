class Map 
{
    private Entity[] objects;
    
    public static function loadFromFile(string filename)
    {
        //1.Открыть файл карты
        //2.Загрузить байты
        //3.Трансформировать байты в соответствующие объекты
        //4.Создать объект карты
        //5.Добавить к ней объекты
        //6.Вернуть объект карты  
    }

    public function update()
    {
        foreach(objects as object) {
            object.update();
        }
    }
}
