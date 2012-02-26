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
private:
    Image image;
    State state;
public:
    Sprite(Image i = SENTIENT_ARROW, State s = FACING_SOUTH) : image(i),state(s) {}

    Image getImage()
    {
        return image;
    }

    Image setImage(Image i = SENTIENT_ARROW)
    {
        image = i;
        return image;
    }

    State getState()
    {
        return state;
    }

    State setState(State s = FACING_SOUTH)
    {
        state = s;
        return state;
    }

    ~Sprite()
    {
    }
};

#endif
