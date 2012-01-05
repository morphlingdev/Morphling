#include "MessageLog.h"

MessageLog::MessageLog(std::string fname) : errors("errors.txt"), log(fname.c_str())
{
    // these should actually be set by something, perhaps display should have a Message Log object
    x = 610;
    y = 0;
}

// used much like the STL standard streams
MessageLog& MessageLog::operator<<(std::string msg)
{
    log << msg;
    messages.push_back(msg);
    return *this;
}

// draws last message onto the display
/// TODO: draw last N messages
void MessageLog::draw_to(Display *dsp)
{
    dsp->fill_rect(x, y, 200, 800, 0, 0, 0); /// HACKY HACK
    dsp->draw_text_block(x, y, 200, messages.back(), Display::FONT_SMALL, 255, 255, 255);
}

void MessageLog::errormsg(std::string msg)
{
}

MessageLog::~MessageLog()
{
}
