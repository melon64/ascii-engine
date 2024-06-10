#include "CursesController.h"
#include "CursesView.h"
#include <variant>

using Action = std::variant<NoAction, KeyboardEvent, MouseEvent>;

CursesController::CursesController(){}

CursesController* CursesController::instance = nullptr;
bool CursesController::instanceFlag = false;

CursesController* CursesController::getInstance(){
    if(!instanceFlag){
        instance = new CursesController();
        instanceFlag = true;
        return instance;
    }
    else{
        return instance;
    }
}

bool CursesController::start(){
    if(!CursesView::getInstance()->start()){
        return false;
    }

    int err = 0;

    err += cbreak();
    err += noecho();
    err += nodelay(stdscr, true);
    err += nonl();
    err += curs_set(0);
    err += mousemask(BUTTON1_CLICKED, NULL);
    err += mousemask(BUTTON2_CLICKED, NULL);
    err += mousemask(BUTTON3_CLICKED, NULL);
    err += keypad(stdscr, true);

    return err == 0;
}

void CursesController::end(){
    curs_set(1);
}

Action CursesController::getAction(){
    int key = getch();
    if(key != ERR){
        MEVENT m_event;
        if (key == KEY_MOUSE && getmouse(&m_event) == OK){
            MouseEvent event;
            Position pos = Position(m_event.x, m_event.y);
            if (m_event.bstate & BUTTON1_CLICKED) {
                event = MouseEvent(pos, LEFT);
            }
            else if (m_event.bstate & BUTTON2_CLICKED) {
                event = MouseEvent(pos, MIDDLE);
            }
            else if (m_event.bstate & BUTTON3_CLICKED) {
                event = MouseEvent(pos, RIGHT);
            }

            return event;
        }
        else{
            KeyboardEvent keyboardEvent;
            keyboardEvent.setKey(key);

            return keyboardEvent;
        }
    }

    return NoAction();

}
