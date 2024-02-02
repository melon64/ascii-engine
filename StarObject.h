#ifndef STAROBJECT_H
#define STAROBJECT_H

#include "Object.h"

class StarObject: public Object{
  public:
    StarObject(Position p);
    ~StarObject();
    void handleEvent(Event* event) override;
};

#endif
