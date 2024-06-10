#ifndef STATE_H
#define STATE_H

#include <string>
#include "Model.h"
#include "EventManager.h"
#include "Object.h"

class State: public Model{
    std::string type;
    bool started;

  protected:
    void setType(std::string);

  public:
    State();
    virtual ~State();
    std::string getType();
    bool isStarted();
    void setStarted(bool b);
    virtual bool start();
    virtual void end();

};

#endif
