#include "Display.h"

/* Changes a single pixel located at (x, y) to RGB values (r, g, b) */
void Display::putpixel(int x, int y, uint8_t r, uint8_t g, uint8_t b)
{
    if(SDL_MUSTLOCK(gScreen)) SDL_LockSurface(gScreen);
    *((Uint32*)gScreen->pixels+gScreen->w*y + x) = SDL_MapRGB(gScreen->format, r, g, b);
    if(SDL_MUSTLOCK(gScreen)) SDL_UnlockSurface(gScreen);
    return;
}

/* Make graphical changes visible */
void Display::update()
{
    SDL_Flip(gScreen);
    return;
}

/* Draw tile such that its upper-left pixel is at (x, y) */
void Display::draw_tile(int x, int y, Tile::TileImgId id)
{
    SDL_Rect srcrect, dstrect;
    dstrect.x = x;
    dstrect.y = y;
    srcrect.x = (id%10)*24;
    srcrect.y = id/10;
    srcrect.w = 24;
    srcrect.h = 24;
    SDL_BlitSurface(tilesheet, &srcrect, gScreen, &dstrect);
    return;
}

void Display::draw_map(int x, int y, Map *m)
{
    draw_map(x, y, m, 0, 0, m->getWidth(), m->getHeight());
	return;
}

void Display::draw_map(int x, int y, Map *m, int mx, int my, int mw, int mh)
{
	for(int i=0;i<mw;i++){
		for(int j=0;j<mh;j++){
			draw_tile(y+i*24, y+j*24, m->tileAt(mx+i, my+j)->getAppearance());
		}
	}
	return;
}

// Moved this functionality into MessageLog class
/*void Display::draw_text(int x, int y, std::string txt, int r, int g, int b)
{
    SDL_Color col;
    SDL_Rect dst;

    col.r = r;
    col.g = g;
    col.b = b;

    dst.x = x;
    dst.y = y;

    SDL_Surface *render = TTF_RenderText_Solid(fnt, txt.c_str(), col);
    SDL_BlitSurface(render, NULL, gScreen, &dst);
    SDL_FreeSurface(render);
}*/

/* Initialize graphics */
Display::Display(int width, int height){
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK) < 0)
    {
        fprintf(stderr, "Unable to init SDL: %s\n", SDL_GetError());
        exit(1);
    }

    SDL_WM_SetIcon(SDL_LoadBMP("icon.bmp"), NULL);
    SDL_WM_SetCaption("Morphling","Morphling");
    if (TTF_Init() == -1)
    {
        printf("Unable to initialize SDL_ttf: %s \n", TTF_GetError());
        exit(2);
    }



    /* Get available fullscreen/hardware modes */
    SDL_Rect ** modes=SDL_ListModes(NULL, SDL_FULLSCREEN|SDL_HWSURFACE);
    /* Check is there are any modes available */
    if(modes == (SDL_Rect **)0)
    {
        exit(-1);
    }
    /* Check if or resolution is restricted */
    if(modes == (SDL_Rect **)-1)
    {
        exit(-2);
    }
    else
    {
        /* Do first mode */
        gScreen = SDL_SetVideoMode(width, height, 32, SDL_SWSURFACE);
        //gScreen = SDL_SetVideoMode(0, 0, 32, SDL_SWSURFACE); //this sets fullscreen
    }


    // If we fail, return error.
    if (gScreen == NULL)
    {
        fprintf(stderr, "Unable to set up video: %s\n", SDL_GetError());
        exit(-3);
    }

    // load tiles.png
    tilesheet = IMG_Load("tiles.png");
}
