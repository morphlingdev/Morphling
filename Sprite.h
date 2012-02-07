#ifndef SPRITE_H
#define SPRITE_H

class Sprite
{
    public:
    enum Image
    {
        SENTIENT_ARROW,
        TAR_IMP,
    };
    enum State
    {
        FACING_SOUTH,
        FACING_EAST,
        FACING_NORTH,
        FACING_WEST
    };
    
    Image image;
    State state;
    
    Sprite()
    {
        image = SENTIENT_ARROW;
        state = FACING_SOUTH;
    }
    
    Sprite(Image i, State s)
    {
        image = i;
        state = s;
    }
    
    ~Sprite()
    {
    }
};

#endif
