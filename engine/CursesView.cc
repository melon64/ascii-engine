#include <ncurses.h>
#include <string>
#include "CursesView.h"
#include "ObjectManager.h"
#include <iostream>

#define MAX_HEIGHT 5

CursesView::CursesView(){}

CursesView *CursesView::instance = nullptr;
bool CursesView::instanceFlag = false;

CursesView* CursesView::getInstance(){
    if(!instanceFlag){
        instance = new CursesView();
        instanceFlag = true;
        return instance;
    }
    else{
        return instance;
    }
}

bool CursesView::start(){
    initscr();
    getmaxyx(stdscr, ydim, xdim);

    mainView = newwin(25, 80, (ydim - 25) / 2, (xdim - 80) / 2);
    //Create the game area subwindow
    gameBuffer1 = derwin(mainView, 20, 78, 1, 1);
    gameBuffer2 = derwin(mainView, 20, 78, 1, 1);
    xdim = 78;
    ydim = 20;
    gameView = gameBuffer1;
    wborder(gameView, '|', '|', '-', '-', '*', '*', '*', '*');

    //Create the status area subwindow
    statusBuffer1 = derwin(mainView, 3, 78, 21, 1);
    statusBuffer2 = derwin(mainView, 3, 78, 21, 1);
    statusView = statusBuffer1;

    //Initial draw
    wrefresh(mainView);
    wrefresh(gameView);
    wrefresh(statusView);

    wrefresh(statusView);

    return true;
}

void CursesView::end(){
    // Clean up
    delwin(gameView);
    delwin(statusView);
    delwin(mainView);
    endwin();
}

void CursesView::notify(ObjectManager *objects, std::string *statuses){
    drawStatus(0, statuses[0]);
    drawStatus(1, statuses[1]);
    drawStatus(2, statuses[2]);

    for(int altitude = 0; altitude < MAX_HEIGHT; altitude++){
        for(int i = 0; i < objects->getSize(); i++){
            Object *obj = objects->getObject(i);
            if(obj->getHeight() == altitude){
                drawFrame(obj->getPosition(), obj->getAnimation().getCurrFrame());
            }
        }
    }

    swapViews();
}

int CursesView::getY(){
    return ydim;
}

int CursesView::getX(){
    return xdim;
}

void CursesView::drawChar(char c, Position p){
    mvwaddch(gameView, p.getY(), p.getX(), c);
}

void CursesView::drawStatus(int i, std::string s){
    mvwprintw(statusView, i, 1, s.c_str());
}

void CursesView::swapViews(){
    wborder(gameView, '|', '|', '-', '-', '*', '*', '*', '*');
    wrefresh(gameView);
    wrefresh(statusView);

    if(gameView == gameBuffer1){
        gameView = gameBuffer2;
        statusView = statusBuffer2;
    }
    else{
        gameView = gameBuffer1;
        statusView = statusBuffer1;
    }

    werase(gameView);
    werase(statusView);
}

// Returns the last drawn buffers
WINDOW* CursesView::getLastGameBuffer(){
    if(gameView == gameBuffer1){
        return gameBuffer2;
    }
    else{
        return gameBuffer1;
    }
}
WINDOW* CursesView::getLastStatusBuffer(){
    if(statusView == statusBuffer1){
        return statusBuffer2;
    }
    else{
        return statusBuffer1;
    }
}

// Returns the current non drawn buffers
WINDOW* CursesView::getNewStatusBuffer(){
    return statusView;
}
WINDOW* CursesView::getNewGameBuffer(){
    return gameView;
}


void CursesView::clear(){
    werase(getLastGameBuffer());
    werase(getLastStatusBuffer());
}

void CursesView::drawFrame(Position p, Frame f){
    for(int i = 0; i < f.getLength(); i++){
        for(int j = 0; j < f.getWidth(); j++){
            mvwaddch(gameView, p.getY() + i, p.getX() + j, f.getWord()[i * f.getWidth() + j]);
        }
    }
}
