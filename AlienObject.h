#ifndef ALIENOBJECT_H
#define ALIENOBJECT_H

#include "Object.h"

class AlienObject: public Object{
    int shotCooldown;
  public:
    AlienObject(Position p);
    ~AlienObject();
    int getShotCooldown();
    void setShotCooldown(int);
    void handleEvent(Event* event) override;
};

#endif
