#include "Map.h"

Tile* Map::tileAt(int x, int y){
	return &(t[x][y]);
}

Map::Map(int w, int h){
	width = w; height = h;
	t = new Tile*[w];
	for(int i=0;i<w;i++) t[i] = new Tile[h];
}

Map::~Map(){
	for(int i=0;i<width;i++) delete t[i];
	delete t;
}