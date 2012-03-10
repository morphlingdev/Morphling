#ifndef MAP_H
#define MAP_H

#include "Tile.h"
#include "Perlin.h"
#include "Entity.h"

#include <vector>

class Map
{
private:
    Tile **t;
    int width, height;
    Perlin elevation, rainfall;
public:
    Tile* tileAt(int x, int y);
    bool passable(int x, int y);
    bool occupied(int x, int y);
    bool safe(int x, int y);
    Entity &entityAt(int x, int y);
    int getWidth()
    {
        return width;
    }
    int getHeight()
    {
        return height;
    }

    void setup(int w, int h);
    void generate_perlin();

    Map(int w, int h);
    Map();
    ~Map();
};

#endif
