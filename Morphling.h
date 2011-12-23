#ifndef MORPHLING_H
#define MORPHLING_H

#include <cstdlib>

#if defined(_MSC_VER)
#include "SDL.h"
#include "SDL_ttf.h"
#include "SDL_image.h"
#else
#include "SDL/SDL.h"
#include "SDL/SDL_ttf.h"
#include "SDL/SDL_image.h"
#endif

#include "Display.h"
#include "Ability.h"
#include "Entity.h"

#define TOTALWIDTH 1024
#define TOTALHEIGHT 768

class Game{
private:
    Display dsp;
    Map M;
    Player P; // the player's own entity
    int P_x;
    int P_y;

public:
    // constructor and destructor
    Game(){};
    ~Game(){};
    
    // functions
    void init();
    int handle_event(SDL_Event &evt);
    void redraw();
};

#endif
