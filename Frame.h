#ifndef FRAME_H
#define FRAME_H

#include <string>
#include "Position.h"

class Frame{
    int length, width;
    std::string word;

  public:
    Frame();
    Frame(int, int, std::string);
    void operator=(const Frame&);
    int getLength();
    int getWidth();
    std::string getWord();
    void setLength(int);
    void setWidth(int);
    void setWord(std::string);
};

#endif
