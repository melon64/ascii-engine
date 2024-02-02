#ifndef MODEL_H
#define MODEL_H

#include "View.h"
#include "Controller.h"
#include "ObjectManager.h"
#include <string>

class Model{
    View *view;
    Controller *controller;
  public:
    void addView(View* view);
    void addController(Controller* controller);
    void notifyView(ObjectManager *objects, std::string *statuses);
    Action getAction();
    bool hasView();
    bool hasController();

};

#endif
