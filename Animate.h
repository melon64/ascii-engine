#ifndef ANIMATE_H
#define ANIMATE_H

#include <string>
#include "Shape.h"
#include "Hitbox.h"

class Animate {
    Shape *shape;
    Frame currFrame; //frame to draw for object
    Hitbox boundary;
    int frameIndex, frameDelayCount;
    std::string label;

  public:
    Animate();
    Shape *getShape();
    Hitbox getBoundary();
    int getFrameIndex();
    int getFrameDelayCount();
    std::string getLabel();
    Frame getCurrFrame();
    void setShape(Shape *newShape);
    void setBoundary(Hitbox newBoundary);
    void setFrameIndex(int newFrameIndex);
    void setFrameDelayCount(int newFrameDelayCount);
    void setLabel(std::string newLabel);
    void update(); //update frameIndex and currFrame based on frameDelayCount

};

#endif
