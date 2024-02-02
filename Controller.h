#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "KeyboardEvent.h"
#include "MouseEvent.h"
#include <variant>

struct NoAction{};

using Action = std::variant<NoAction, KeyboardEvent, MouseEvent>;

class Controller{
  public:
    virtual Action getAction() = 0;
};

#endif
