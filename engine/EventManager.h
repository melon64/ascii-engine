#ifndef EVENTMANAGER_H
#define EVENTMANAGER_H

#include "Event.h"
#include <vector>

class EventManager {
    std::vector<Event *> events;
    int size;

  public:
    EventManager();
    ~EventManager();
    Event *operator[](int index);
    void addEvent(Event *e);
    void removeEvent(Event *e);
    void removeEvent(int index);
    Event *getEvent(int index);
    int getSize();
    void clear();

};

#endif
