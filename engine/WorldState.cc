#include "WorldState.h"
#include "CollisionEvent.h"
#include "DespawnEvent.h"
#include "RefreshEvent.h"

#define NUM_STATUSES 3

WorldState::WorldState(){
    objects = new ObjectManager();
    objectsToDespawn = new ObjectManager();
    statuses = new std::string[NUM_STATUSES];
    events = new EventManager();
    validEvents.push_back("CollisionEvent");
    validEvents.push_back("MouseEvent");
    validEvents.push_back("KeyboardEvent");
    validEvents.push_back("DespawnEvent");
    validEvents.push_back("RefreshEvent");
}

bool WorldState::instanceFlag = false;
WorldState *WorldState::instance = nullptr;

WorldState *WorldState::getInstance() {
    if(!instanceFlag){
        instance = new WorldState();
        instanceFlag = true;
        return instance;
    }
    else{
        return instance;
    }
}

bool WorldState::start() {
    events->clear();
    objects->clear();
    objectsToDespawn->clear();
    return true;
}

void WorldState::end() {
    objects->clear();
    objectsToDespawn->clear();
    events->clear();
    delete events;
    delete objects;
    delete objectsToDespawn;
    delete[] statuses;

}

void WorldState::insertObject(Object *o) {
    o->addEvent("RefreshEvent");
    objects->addObject(o);
}

void WorldState::removeObject(Object *o) {
    objects->removeObject(o);
}

void WorldState::markObjectForDespawn(Object *o) {
    objectsToDespawn->addObject(o);
}

ObjectManager *WorldState::getObjects() {
    return objects;
}

ObjectManager *WorldState::getObjectsToDespawn() {
    return objectsToDespawn;
}

Hitbox WorldState::getBoundary() {
    return boundary;
}

Hitbox WorldState::getPlayerViewBox() {
    return playerViewBox;
}

Position WorldState::getPlayerViewBoxOffset() {
    return playerViewBoxOffset;
}

Object *WorldState::getPlayer() {
    return player;
}

void WorldState::setBoundary(Hitbox h) {
    boundary = h;
}

void WorldState::setPlayerViewBox(Hitbox h) {
    playerViewBox = h;
}

void WorldState::setPlayerViewBoxOffset(Position p) {
    playerViewBoxOffset = p;
}

void WorldState::setPlayer(Object *o) {
    player = o;
    o->addEvent("MouseEvent");
    o->addEvent("KeyboardEvent");
}

void WorldState::changeStatus(int i, std::string s) {
    //i must be less than NUM_STATUSES
    statuses[i] = s;
}

std::string *WorldState::getStatuses() {
    return statuses;
}

void WorldState::update() {
    for(int i = 0; i < objects->getSize(); i++){
        Object *o = objects->getObject(i);
        Position p = o->update();
        if (moveObject(o, p)){
            o->setPosition(p);
            o->getHitbox().setPosition(p);
        }
    }
    //despawn out of bounds objects
    despawnObjects();
    //check for collisions
    manageCollisions();

    for(int i = 0; i < objectsToDespawn->getSize(); i++){
        objects->removeObject(objectsToDespawn->getObject(i));
    }
    objectsToDespawn->clear();
}

bool WorldState::moveObject(Object *o, Position p) {
    //check if new pos is same as old pos
    bool collided = false;
    if (p.getX() == o->getPosition().getX() && p.getY() == o->getPosition().getY()){
        return false;
    }
    if (o->getSolidity() == FOG){
        return true;
    }

    if (p.getX() <= boundary.getPosition().getX()){
        Position poi = Position(boundary.getPosition().getX(), p.getY());
        CollisionEvent *ce = new CollisionEvent(o, nullptr, poi);
        o->handleEvent(ce);
        delete ce;
        // changeStatus(0, "Collision with left boundary");
        collided = true;
    }

    if (p.getX() + o->getHitbox().getWidth() >= boundary.getPosition().getX() + boundary.getLength()){
        Position poi = Position(boundary.getPosition().getX() + boundary.getLength(), p.getY());
        CollisionEvent *ce = new CollisionEvent(o, nullptr, poi);
        o->handleEvent(ce);
        delete ce;
        // changeStatus(0, "Collision with right boundary");
        collided = true;
    }
    if (p.getY() <= boundary.getPosition().getY()){
        Position poi = Position(p.getX(), boundary.getPosition().getY());
        CollisionEvent *ce = new CollisionEvent(o, nullptr, poi);
        o->handleEvent(ce);
        delete ce;
        // changeStatus(0, "Collision with top boundary");
        collided = true;
    }
    if (p.getY() + o->getHitbox().getLength() >= boundary.getPosition().getY() + boundary.getWidth()){
        Position poi = Position(p.getX(), boundary.getPosition().getY() + boundary.getWidth());
        CollisionEvent *ce = new CollisionEvent(o, nullptr, poi);
        o->handleEvent(ce);
        delete ce;
        // changeStatus(0, "Collision with bottom boundary");
        collided = true;
    }

    bool outOfBounds = false;
    if (p.getX() < boundary.getPosition().getX() || p.getX() + o->getHitbox().getLength() > boundary.getPosition().getX() + boundary.getLength()){
        outOfBounds = true;
    }

    if (o->getSolidity() == SOFT){
        if (outOfBounds){
            o->setDespawnCount(o->getDespawnCount() + 1);
        }
        else{
            o->setDespawnCount(0);
        }
        return true;
    }

    else if (o->getSolidity() == SOLID){
        if (collided){
            return false;
        }
        else{
            return true;
        }
    }

    return true;
}

void WorldState::despawnObjects(){
    //check each objects despawn count, if it is equal to its time to despawn, then despawn it
    for(int i = 0; i < objects->getSize(); i++){
        Object *o = objects->getObject(i);
        if (o->getDespawnCount() == o->getTimeToDespawn()){
            objectsToDespawn->addObject(o);
            DespawnEvent *de = new DespawnEvent();
            o->handleEvent(de);
            delete de;
        }
    }
}

//delete these events in object handler btw
void WorldState::manageCollisions() {
    //check for collisions
    for(int i = 0; i < objects->getSize(); i++){
        Object *o1 = objects->getObject(i);
        for(int j = i + 1; j < objects->getSize(); j++){
            Object *o2 = objects->getObject(j);
            if (o1->getHitbox().isColliding(o2->getHitbox())){
                if (o1->getSolidity() == FOG || o2->getSolidity() == FOG){
                    continue;
                }
                else if(o1->getSolidity() == SOLID && o2->getSolidity() == SOLID){
                    Position prev1 = o1->getPrevPosition();
                    Position prev2 = o2->getPrevPosition();

                    o1->setPosition(o1->getPrevPosition());
                    o2->setPosition(o2->getPrevPosition());

                    CollisionEvent *ce = new CollisionEvent(o1, o2, o1->getPosition());
                    o1->handleEvent(ce);
                    delete ce;
                    ce = new CollisionEvent(o2, o1, o2->getPosition());
                    o2->handleEvent(ce);
                    delete ce;

                    continue;
                }
                else if (o1->getSolidity() == SOFT || o2->getSolidity() == SOFT){
                    CollisionEvent *ce = new CollisionEvent(o1, o2, o1->getPosition());
                    o1->handleEvent(ce);
                    delete ce;
                    ce = new CollisionEvent(o2, o1, o2->getPosition());
                    o2->handleEvent(ce);
                    delete ce;

                    continue;
                }
            }
        }
    }
}

bool WorldState::isValidEvent(std::string e){
    if (std::find(validEvents.begin(), validEvents.end(), e) != validEvents.end()){
        return true;
    }
    return false;
}

void WorldState::registerObserver(Object *observer, std::string event){
    if (isValidEvent(event)){
        observer->addEvent(event);
    }
    else{
        validEvents.push_back(event);
        observer->addEvent(event);
    }
}

void WorldState::removeObserver(Object *observer, std::string event){
    if (isValidEvent(event)){
        observer->removeEvent(event);
    }
}

void WorldState::notifyObservers(Event *e){
    for(int i = 0; i < objects->getSize(); i++){
        Object *o = objects->getObject(i);
        if (o->hasEvent(e->getType())){
            o->handleEvent(e);
        }
    }
}


//TODO
//handle events by iterating through all objects
//checking if they have the event
//and then calling the event
//main events will be in game loop
//but other events will be handled here (collision, etc.)
//collision will be update all objects first
//then check for collision between all including border
//then handle collision for each objects own events
