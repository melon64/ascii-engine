#ifndef COINOBJECT_H
#define COINOBJECT_H

#include "Object.h"

class CoinObject : public Object{
  public:
    CoinObject(Position p);
    ~CoinObject();
    void handleEvent(Event* event) override;
};

#endif
