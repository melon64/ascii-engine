#ifndef VIEW_H
#define VIEW_H

#include "ObjectManager.h"
#include <string>

class View {
  public:
    virtual void notify(ObjectManager *objects, std::string *statuses) = 0;
};

#endif
