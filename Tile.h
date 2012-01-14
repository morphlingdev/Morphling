#ifndef TILE_H
#define TILE_H

class Tile
{
public:

    enum TileImgId
    {
        IMG_GRASS, IMG_LAVA, IMG_WATER, IMG_DEEPWATER, IMG_SAND, IMG_ROCK, IMG_MOUNTAIN, IMG_FOREST, IMG_WETLAND
    };

private:
    TileImgId appearance;
public:

    TileImgId getAppearance()
    {
        return appearance;
    }
    void setAppearance(TileImgId appearance)
    {
        this->appearance = appearance;
    }
    Tile(TileImgId appearance=IMG_GRASS)
    {
        setAppearance(appearance);
    }
};

#endif
