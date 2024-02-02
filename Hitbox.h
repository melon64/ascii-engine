#ifndef HITBOX_H
#define HITBOX_H

#include "Position.h"

class Hitbox {
    Position position;
    int length, width;

  public:
    Hitbox();
    Hitbox(Position, int, int);
    bool operator==(const Hitbox&);
    Position getPosition();
    int getLength();
    int getWidth();
    void setPosition(Position);
    void setLength(int);
    void setWidth(int);
    bool isColliding(Hitbox h);

};

#endif
