#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "State.h"
#include "Controller.h"

#define DEFAULT_REFRESH_RATE 33

class GameState: public State {
    GameState();
    static GameState *instance;
    static bool instanceFlag;
    GameState(GameState const&) = delete;
    void operator=(GameState const&) = delete;

    int iterCount;
    bool gameOver;
    int refreshRate;
    
  public:
    static GameState *getInstance();
    bool isGameOver();
    void setGameOver(bool b);
    int getRefreshRate();
    void setRefreshRate(int r);
    int getIterCount();
    void setIterCount(int i);

    void go(int refreshRate = DEFAULT_REFRESH_RATE);

    bool start();
    void end();
    void processAction(Action action);
};

#endif
