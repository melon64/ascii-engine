#ifndef OBJECTMANAGER_H
#define OBJECTMANAGER_H

#include "Object.h"
#include <vector>

class Object;

class ObjectManager {
    std::vector<Object *> objects;
    int size;

  public:
    ObjectManager();
    ~ObjectManager();
    Object *operator[](int index);
    void addObject(Object *o);
    void removeObject(Object *o);
    void removeObject(int index);
    Object *getObject(int index);
    int getSize();
    void clear();

};

#endif
