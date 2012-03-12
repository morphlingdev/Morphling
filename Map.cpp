#include "Map.h"
#include <cstdlib>

Tile* Map::tileAt(int x, int y)
{
    return &(t[x][y]);
}

bool Map::passable(int x, int y)
{
    if(t[x][y].getAppearance() == Tile::IMG_MOUNTAIN) return false;
    return true;
}

bool Map::occupied(int x, int y)
{
    if(t[x][y].occupant == NULL) return false;
    else return true;
}

bool Map::safe(int x, int y)
{
    Tile::TileImgId i = t[x][y].getAppearance();
    if(i==Tile::IMG_DEEPWATER || i==Tile::IMG_LAVA) return false;

    return true;
}

Entity &Map::entityAt(int x, int y){
    return *t[x][y].occupant;
}

void Map::setup(int w, int h)
{
    width = w;
    height = h;
    t = new Tile*[w];
    for(int i=0; i<w; i++) t[i] = new Tile[h];
}

void Map::generate_perlin()
{
    //Initialize Perlin Noise
    elevation = Perlin(5, 0.5, 0.1, std::rand());
    rainfall = Perlin(5, 0.5, 0.1, std::rand());
    //5 octaves, 0.5 persistance (roughness, high is more rough), 0.1 zoom (1.0 is "each tile completely random"), random seed

    for(int i = 0; i < getWidth(); i++)
    {
        for(int j = 0; j < getHeight(); j++)
        {
            double e = elevation.n(i, j);
            double r = rainfall.n(i, j);
            if(e > 0.9)
            {
                t[i][j].setAppearance(Tile::IMG_MOUNTAIN);
            }
            else if(e > 0.7)
            {
                t[i][j].setAppearance(Tile::IMG_ROCK);
            }
            else if(e > 0.1)
            {
                if(r > 0.95)
                {
                    t[i][j].setAppearance(Tile::IMG_WETLAND);
                }
                else if(r > 0.3)
                {
                    t[i][j].setAppearance(Tile::IMG_FOREST);
                }
                else if(r > -0.9)
                {
                    t[i][j].setAppearance(Tile::IMG_GRASS);
                }
                else
                {
                    t[i][j].setAppearance(Tile::IMG_SAND);
                }
            }
            else if(e > -0.2)
            {
                if(r > 0.9)
                {
                    t[i][j].setAppearance(Tile::IMG_WETLAND);
                }
                else
                {
                    t[i][j].setAppearance(Tile::IMG_SAND);
                }
            }
            else if(e > -0.3)
            {
                if(r > -0.8)
                {
                    t[i][j].setAppearance(Tile::IMG_WATER);
                }
                else
                {
                    t[i][j].setAppearance(Tile::IMG_WETLAND);
                }
            }
            else if(e > -0.7)
            {
                t[i][j].setAppearance(Tile::IMG_WATER);
            }
            else
            {
                t[i][j].setAppearance(Tile::IMG_DEEPWATER);
            }
        }
    }
}

Map::Map(int w, int h)
{
    setup(w, h);
}

Map::Map()
{
    setup(10, 10);
}

Map::~Map()
{
    for(int i=0; i<width; i++) delete t[i];
    delete t;
}
