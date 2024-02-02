#ifndef REFRESHEVENT_H
#define REFRESHEVENT_H

#include "Event.h"

class RefreshEvent: public Event{
    int refreshes;
  public:
    RefreshEvent();
    ~RefreshEvent();
    int getRefreshes();
    void setRefreshes(int);
};

#endif
