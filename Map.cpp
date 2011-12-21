#include "Map.h"

Tile* Map::tileAt(int x, int y){
	return &(t[x][y]);
}

Map::Map(int w, int h){
	width = w; height = h;
	t = new Tile*[w];
	for(int i=0;i<w;i++) t[i] = new Tile[h];

	//Initialize Perlin Noise
	p = Perlin(5, 0.5, 0.01, 1234)
	//5 octaves, 0.5 persistance (roughness, high is more rough), 0.01 zoom (1.0 is "each tile completely random"), 1234 seed (should be random)

	for(int i = 0; i < w; i++)
	{
        for(int j = 0;j < h; j++)
        {
            if(p.n(i, j) > 0.0) //Temporary placeholder... eventually it will do something more impressive
            {
                t[i][j].setAppearance(1);
            }
        }
	}
}

Map::~Map(){
	for(int i=0;i<width;i++) delete t[i];
	delete t;
}
