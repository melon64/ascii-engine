#ifndef RECTANGLEOBJECT_H
#define RECTANGLEOBJECT_H

#include "Object.h"


class RectangleObject: public Object{
  public:
    RectangleObject(char c, int length, int width, Position p, std::string label); //label is resource name
    ~RectangleObject();
    void handleEvent(Event* event) override;
};

#endif
