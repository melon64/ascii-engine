#ifndef EVENT_H
#define EVENT_H

#include "ObjectManager.h"
#include <string>

class Event {
    std::string type;
    
  public:
    Event();
    virtual ~Event();
    std::string getType();
    void setType(std::string);

};

#endif
