#ifndef BOXOBJECT_H
#define BOXOBJECT_H

#include "Object.h"


class BoxObject: public Object{
  public:
    BoxObject(char c, int length, int width, Position p, std::string label); //label is resource name
    ~BoxObject();
    void handleEvent(Event* event) override;
};

#endif
