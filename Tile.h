#ifndef TILE_H
#define TILE_H

#include "Display.h"

class Tile
{
  Display::TileImgId appearance;
public:
  Tile(){
		this->appearance = Display::TILE_LAVA;
  }
  Tile(Display::TileImgId appearance){
		this->appearance = appearance;
  }
};

#endif
