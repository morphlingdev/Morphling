#include "Map.h"

Map::Map(int w, int h){
	width = w; height = h;
	t = new Tile[w][h];
}

Map::~Map(){
	delete Tile;
}