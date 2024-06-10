#ifndef _WORLDSTATE_H_
#define _WORLDSTATE_H_

#include "Object.h"
#include "State.h"
#include "ObjectManager.h"
#include "EventManager.h"

const int maxHeight = 4;

class WorldState: public State {
    WorldState();
    WorldState(const WorldState&) = delete;
    void operator=(const WorldState&) = delete;
    static bool instanceFlag;
    static WorldState *instance;

    ObjectManager *objects;
    ObjectManager *objectsToDespawn;
    Hitbox boundary;
    Hitbox playerViewBox;
    Position playerViewBoxOffset;
    Object *player;

    std::string *statuses;
    EventManager *events;
    std::vector<std::string> validEvents;


  public:
    static WorldState *getInstance();
    bool start() override;
    void end() override;
    void insertObject(Object *o);
    void removeObject(Object *o);
    void markObjectForDespawn(Object *o);
    ObjectManager *getObjects();
    ObjectManager *getObjectsToDespawn();
    Hitbox getBoundary();
    Hitbox getPlayerViewBox();
    Position getPlayerViewBoxOffset();
    Object *getPlayer();
    void setBoundary(Hitbox h);
    void setPlayerViewBox(Hitbox h);
    void setPlayerViewBoxOffset(Position p);
    void setPlayer(Object *o);
    void update();
    bool moveObject(Object *o, Position p);
    void manageCollisions();
    void changeStatus(int i, std::string s);
    std::string *getStatuses();
    void despawnObjects();

    bool isValidEvent(std::string event);
    void registerObserver(Object *observer, std::string event);
    void removeObserver(Object *observer, std::string event);
    void notifyObservers(Event *e);

};

#endif
