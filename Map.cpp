#include "Map.h"
#include <cstdlib>

Tile* Map::tileAt(int x, int y){
	return &(t[x][y]);
}

void Map::setup(int w, int h){
	width = w; height = h;
	t = new Tile*[w];
	for(int i=0;i<w;i++) t[i] = new Tile[h];
}

void Map::generate_perlin(){
	//Initialize Perlin Noise
	p = Perlin(5, 0.5, 0.1, std::rand());
	//5 octaves, 0.5 persistance (roughness, high is more rough), 0.1 zoom (1.0 is "each tile completely random"), random seed

	for(int i = 0; i < getWidth(); i++)
	{
        for(int j = 0;j < getHeight(); j++)
        {
            //Temporary placeholder... eventually it will do something more impressive
            if(p.n(i, j) > 0.7)
            {
                t[i][j].setAppearance(4); // mountain
            }
            else if(p.n(i, j) > 0.1)
            {
                t[i][j].setAppearance(0); // grass
            }
            else if(p.n(i, j) > -0.2)
            {
                t[i][j].setAppearance(3); // sand
            }
            else
            {
                t[i][j].setAppearance(2); // water
            }
        }
	}
}

Map::Map(int w, int h){
    setup(w, h);
}

Map::Map(){
}

Map::~Map(){
	for(int i=0;i<width;i++) delete t[i];
	delete t;
}
