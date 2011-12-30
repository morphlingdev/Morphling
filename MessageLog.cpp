#include "MessageLog.h"

MessageLog::MessageLog(std::string fname, SDL_Surface* s) : errors("errors.txt"), log(fname.c_str()), gScreen(s)
{
    col.r = 0;
    col.g = 0;
    col.b = 0;

    // these should actually be set by something, perhaps display should have a Message Log object
    x = 610;
    y = 0;

    // load font
    fnt = TTF_OpenFont("DejaVuSans.ttf", 12);

}

// we need to fix this to properly use a queue of messages
MessageLog& MessageLog::operator<<(std::string msg)
{
    log << msg;

    SDL_Color col;
    SDL_Rect dst;

    dst.x = x;
    dst.y = y;

    SDL_Surface *render = TTF_RenderText_Solid(fnt, msg.c_str(), col);
    SDL_BlitSurface(render, NULL, gScreen, &dst);
    SDL_FreeSurface(render);

    return *this;
}

void MessageLog::errormsg(std::string msg)
{

}

MessageLog::~MessageLog()
{
    TTF_CloseFont(fnt);
}
