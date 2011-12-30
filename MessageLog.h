#ifndef MESSAGELOG_H
#define MESSAGELOG_H


#if defined(_MSC_VER)
#include "SDL.h"
#include "SDL_ttf.h"
#include "SDL_image.h"
#else
#include "SDL/SDL.h"
#include "SDL/SDL_ttf.h"
#include "SDL/SDL_image.h"
#endif


#include <fstream>
#include <queue>

class MessageLog
{
    private:
    std::ofstream errors;
    std::ofstream log;
    int x;
    int y;
    SDL_Color col;
    TTF_Font *fnt;
    std::queue<std::string> messages;
    SDL_Surface* gScreen;

    public:
    MessageLog& operator<<(std::string msg);
    void errormsg(std::string msg);
    MessageLog(std::string fname, SDL_Surface* s);
    ~MessageLog();
};

#endif
