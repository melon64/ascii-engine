#ifndef PLAYEROBJECT_H
#define PLAYEROBJECT_H

#include "Object.h"

class PlayerObject: public Object{
  public:
    PlayerObject();
    ~PlayerObject();
    void handleEvent(Event* event) override;
};

#endif
