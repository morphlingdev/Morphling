#include "Display.h"

/* Changes a single pixel located at (x, y) to RGB values (r, g, b) */
void Display::putpixel(int x, int y, uint8_t r, uint8_t g, uint8_t b){
	if(SDL_MUSTLOCK(screen)) SDL_LockSurface(screen);
	screen->pixels[screen->w*x + y] = SDL_MapRGB(screen->format, r, g, b);
	if(SDL_MUSTLOCK(screen)) SDL_UnlockSurface(screen);
	return;
}

/* Initiates graphics */
Display::Display(int width, int height){
	screen = SDL_SetVideoMode(width, height, 32, SDL_SWSURFACE);
}
