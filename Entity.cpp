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
