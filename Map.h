#ifndef MAP_H
#define MAP_H

#include "Tile.h"

class Map
{
private:
	Tile **t;
	int width, height;
public:
	Tile* tileAt(int x, int y);
	int getWidth(){ return width; }
	int getHeight(){ return height; }
	Map(int w, int h);
	~Map();
};

#endif
