#ifndef SHAPE_H
#define SHAPE_H

#include "Frame.h"
#include "Position.h"

class Shape {
    int length, width;
    int frameCount, maxFrameCount;
    int frameDelay;
    Frame *frames;
    std::string label;
    Shape();

  public:
    Shape(int maxFrameCount);
    ~Shape();
    int getLength();
    int getWidth();
    int getFrameCount();
    int getMaxFrameCount();
    int getFrameDelay();
    Frame getFrame(int index);
    std::string getLabel();
    void setLength(int);
    void setWidth(int);
    void setFrameDelay(int);
    void addFrame(Frame frame);
    void setLabel(std::string);
};

#endif
