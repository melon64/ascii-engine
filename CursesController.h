#ifndef CURSESCONTROLLER_H
#define CURSESCONTROLLER_H

#include "Controller.h"
#include <variant>

using Action = std::variant<NoAction, KeyboardEvent, MouseEvent>;

class CursesController : public Controller{
    static CursesController* instance;
    static bool instanceFlag;
    CursesController();
    CursesController(CursesController const&) = delete;
    void operator=(CursesController const&) = delete;

  public:
    Action getAction();
    static CursesController *getInstance();
    bool start();
    void end();
};

#endif
