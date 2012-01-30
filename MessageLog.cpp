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
	// I don't know the width of the log
	// So I can't manipulate it
    log << msg << std::flush;
    messages.push_back(msg);
    return *this;
}



// draws messages onto the display until width and height in pixels is reached
void MessageLog::draw_to(Display *dsp, int width, int height)
{
    int height_drawn = 0;
    dsp->fill_rect(x, y, 600, height+100, 0, 0, 0);
    for(int i=messages.size()-1; height_drawn<height && i>=0; i--){
        height_drawn += dsp->draw_text_block(x, y+height_drawn, width, messages[i], Display::FONT_SMALL, 255, 255, 255);
    }
}

// draws messages onto the display until 600 pixels of height are reached
void MessageLog::draw_to(Display *dsp)
{
    draw_to(dsp, 400, 600);
}

void MessageLog::errormsg(std::string msg)
{
}

MessageLog::~MessageLog()
{
    log.close();
}

