#!/bin/sh
i486-mingw32-windres Morphling.rc -O coff -o Morphling.res
i486-mingw32-g++ -o Morphling.exe Morphling.cpp Display.cpp Ability.cpp Map.cpp Tile.cpp Entity.cpp MessageLog.cpp Item.cpp Morphling.res `/usr/i486-mingw32/bin/sdl-config --cflags --libs` -lSDL_ttf -lSDL_image -static-libgcc -static-libstdc++
