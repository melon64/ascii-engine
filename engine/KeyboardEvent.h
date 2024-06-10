#ifndef KEYBOARDEVENT_H
#define KEYBOARDEVENT_H

#include "Event.h"
#include <string>

class KeyboardEvent : public Event{
    int key;

  public:
    KeyboardEvent();
    KeyboardEvent(int key);
    int getKey();
    void setKey(int key);
};

#endif
