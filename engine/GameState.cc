#include <iostream>
#include <time.h>
#include <variant>

#include "GameState.h"

#include "WorldState.h"
#include "Clock.h"
#include "Event.h"
#include "Hitbox.h"
#include "CursesView.h"
#include "CursesController.h"
#include "RefreshEvent.h"


GameState *GameState::instance = nullptr;
bool GameState::instanceFlag = false;

GameState *GameState::getInstance() {
    if(!instanceFlag){
        instance = new GameState();
        instanceFlag = true;
        return instance;
    }
    else{
        return instance;
    }
}


GameState::GameState() {
    iterCount = 0;
    gameOver = false;
    refreshRate = DEFAULT_REFRESH_RATE;
}

bool GameState::start() {
    WorldState *world = WorldState::getInstance();
    world->start();
    
    if(!hasController() || !hasView()) {
        return false;
    }

    CursesView *view = CursesView::getInstance();
    view->start();
    Hitbox boundary = Hitbox(Position(0, 0), view->getX(), view->getY());
    world->setBoundary(boundary);

    CursesController::getInstance()->start();

    return true;
}

void GameState::end() {
    WorldState *world = WorldState::getInstance();
    world->end();

    CursesView *view = CursesView::getInstance();
    view->end();

    CursesController *controller = CursesController::getInstance();
    controller->end();
}


bool GameState::isGameOver() {
    return gameOver;
}

void GameState::setGameOver(bool b) {
    gameOver = b;
}

int GameState::getRefreshRate() {
    return refreshRate;
}

void GameState::setRefreshRate(int r) {
    refreshRate = r;
}

int GameState::getIterCount() {
    return iterCount;
}

void GameState::setIterCount(int i) {
    iterCount = i;
}

void GameState::go(int refreshRate) {
    this->refreshRate = refreshRate;
    Clock clock = Clock();
    WorldState *world = WorldState::getInstance();
    RefreshEvent *event = new RefreshEvent();

    while(!gameOver) {
        clock.delta();
        world->notifyObservers(event);
        processAction(getAction());
        world->update();
        notifyView(world->getObjects(), world->getStatuses());
        iterCount++;
        event->setRefreshes(iterCount);
        long int loop_time = clock.split();
        struct timespec sleep_time;
        sleep_time.tv_sec = 0;
        sleep_time.tv_nsec = refreshRate * 1000000 - loop_time;
        nanosleep(&sleep_time, NULL);
    }

    delete event;
}


void GameState::processAction(Action action) {
    WorldState *world = WorldState::getInstance();
    if(!std::holds_alternative<NoAction>(action)){
        if(std::holds_alternative<KeyboardEvent>(action)){
            KeyboardEvent *event = new KeyboardEvent(std::get<KeyboardEvent>(action));
            world->notifyObservers(event);
            delete event;
        }
        else if(std::holds_alternative<MouseEvent>(action)){
            MouseEvent *event = new MouseEvent(std::get<MouseEvent>(action));
            world->notifyObservers(event);
            delete event;
        }
    }
}
