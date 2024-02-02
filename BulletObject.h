#ifndef BULLETOBJECT_H
#define BULLETOBJECT_H

#include "Object.h"

class BulletObject: public Object{
    bool shotByPlayer;
  public:
    BulletObject(Position p, Position d, bool player);
    ~BulletObject();
    bool isShotByPlayer();
    void setShotByPlayer(bool);
    void handleEvent(Event* event) override;
};

#endif
