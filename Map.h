#ifndef MAP_H
#define MAP_H

#include "Tile.h"
#include "Perlin.h"

class Map
{
private:
	Tile **t;
	int width, height;
	Perlin p;
public:
	Tile* tileAt(int x, int y);
	int getWidth(){ return width; }
	int getHeight(){ return height; }
	
	void setup(int w, int h);
	void generate_perlin();
	
	Map(int w, int h);
	Map();
	~Map();
};

#endif
