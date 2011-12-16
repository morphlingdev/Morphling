#ifndef MAP_H
#define MAP_H

#include "Tile.h"

class Map
{
private:
	Tile **t;
	int width, height;
public:
	Map(int w, int h);
	~Map();
};

#endif
