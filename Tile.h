#ifndef TILE_H
#define TILE_H

class Tile
{
	int appearance;
public:
	int getAppearance(){ return appearance; }
	int setAppearance(int appearance){ this->appearance = appearance; }
	Tile(int appearance=0){
		this->appearance = appearance;
	}
};

#endif
