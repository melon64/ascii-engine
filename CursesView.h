#ifndef CURSESVIEW_H
#define CURSESVIEW_H

#include "View.h"
#include <ncurses.h>
#include <string>
#include "Position.h"
#include "Frame.h"
#include "ObjectManager.h"

class CursesView: public View {
    CursesView();
    CursesView(const CursesView&) = delete;
    CursesView& operator=(const CursesView&) = delete;
    WINDOW *gameView;
    WINDOW *gameBuffer1;
    WINDOW *gameBuffer2;
    WINDOW *statusView;
    WINDOW *statusBuffer1;
    WINDOW *statusBuffer2;
    WINDOW *mainView;
    int xdim, ydim;
    static CursesView *instance;
    static bool instanceFlag;

  public:
    static CursesView *getInstance();
    bool start();
    void end();
    void notify(ObjectManager *objects, std::string *statuses) override;
    int getY();
    int getX();
    void drawChar(char c, Position p);
    void drawFrame(Position p, Frame f);
    void drawStatus(int i, std::string s);
    void swapViews();
    WINDOW *getLastGameBuffer();
    WINDOW *getNewGameBuffer();
    WINDOW *getLastStatusBuffer();
    WINDOW *getNewStatusBuffer();
    void clear();
};

#endif
