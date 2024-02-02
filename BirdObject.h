#ifndef BIRDOBJECT_H
#define BIRDOBJECT_H

#include "Object.h"

class BirdObject: public Object{
    int score;
    int pipeCount;
    bool lost;
  public:
    BirdObject();
    ~BirdObject();
    int getScore();
    void setScore(int);
    void handleEvent(Event* event) override;
};

#endif
