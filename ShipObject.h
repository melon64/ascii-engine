#ifndef SHIPOBJECT_H
#define SHIPOBJECT_H

#include "Object.h"

class ShipObject: public Object{
    int score;
    int lives;
    int bulletCooldown;
    bool powerup;
    int powerupDuration;
    int timeWon;
  public:
    ShipObject();
    ~ShipObject();
    void setScore(int);
    void setLives(int);
    void setBulletCooldown(int);
    int getScore();
    int getLives();
    int getBulletCooldown();
    void handleEvent(Event* event) override;
};

#endif

