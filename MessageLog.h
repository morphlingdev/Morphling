#ifndef MESSAGELOG_H
#define MESSAGELOG_H

#include <fstream>
#include <queue>

#include "Display.h"

class MessageLog
{
private:
    std::ofstream errors;
    std::ofstream log;
    int x;
    int y;
    std::vector<std::string> messages;

public:
    // writing messages
    MessageLog& operator<<(std::string msg);
    void errormsg(std::string msg);

    // drawing to display
    void draw_to(Display *dsp, int width, int height);
    void draw_to(Display *dsp);

    // constructor and destructor
    MessageLog(std::string fname);
    ~MessageLog();
};

#endif
