#include "Object.h"
#include "Hitbox.h"
#include "Frame.h"
#include "Event.h"
#include "Position.h"
#include "Animate.h"
#include "Resources.h"
#include "WorldState.h"
#include <string>

#define MAX_HEIGHT 5
#define DEFAULT_DESPAWN_TIME 10

static int id = 0;

Object::Object(){
  id = id++;
  position = Position();
  hitbox = Hitbox();
  height = 0;
  eventCount = 0;
  WorldState *ws = WorldState::getInstance();
  ws->insertObject(this);
  int timeToDespawn = DEFAULT_DESPAWN_TIME;
  int despawnCount = 0;
}

Object::~Object(){
    WorldState *ws = WorldState::getInstance();
    ws->removeObject(this);
    for (int i = 0; i < eventCount; i++){
        this->removeEvent(events[i]);
    }
}

int Object::getId(){
    return id;
}
std::string Object::getType(){
    return type;
}
Position Object::getPosition(){
    return position;
}
Hitbox Object::getHitbox(){
    return hitbox;
}
Animate Object::getAnimation(){
    return animation;
}
std::string Object::getResourceName(){
    return resourceName;
}
Position Object::getDirection(){
    return direction;
}
int Object::getVelocity(){
    return velocity;
}
int Object::getVelocityDelay(){
    return velocityDelay;
}
int Object::getHeight(){
    return height;
}
Solidity Object::getSolidity(){
    return solidity;
}

void Object::setId(int id){
    this->id = id;
}

void Object::setType(std::string type){
    this->type = type;
}

void Object::setPosition(Position newPos){
    if (prevPosition.getX() != newPos.getX() || prevPosition.getY() != newPos.getY()){
        prevPosition = position;
    }
    position = newPos;
    hitbox.setPosition(newPos);
}

void Object::setHitbox(Hitbox hitbox){
    this->hitbox = hitbox;
}

void Object::setAnimation(Animate animation){
    this->animation = animation;
}

void Object::setResourceName(std::string resourceName){
    this->resourceName = resourceName;
}

void Object::setDirection(Position direction){
    this->direction = direction;
}

void Object::setVelocity(int velocity){
    this->velocity = velocity;
}

void Object::setVelocityDelay(int velocityDelay){
    this->velocityDelay = velocityDelay;
}

void Object::setHeight(int height){
    this->height = height;
}

void Object::setSolidity(Solidity solidity){
    this->solidity = solidity;
}

void Object::setShape(std::string resource){
    Resources *r = Resources::getInstance();
    Shape *sh = r->getShape(resource);
    animation.setShape(sh);
    hitbox.setLength(sh->getLength());
    hitbox.setWidth(sh->getWidth());
    hitbox.setPosition(position);
}

void Object::setPrevPosition(Position prevPosition){
    this->prevPosition = prevPosition;
}

void Object::setStaticPosition(Position staticPosition){
    this->position = staticPosition;
    this->prevPosition = staticPosition;
}

Position Object::getPrevPosition(){
    return prevPosition;
}

Position Object::update(){
    animation.update();
    if (velocityCount < velocityDelay){
        velocityCount++;
        return position;
    }
    velocityCount = 0;
    Position temp;
    temp.setX(position.getX() + direction.getX() * velocity);
    temp.setY(position.getY() + direction.getY() * velocity);
    // hitbox.setPosition(position);
    return temp;
}

void Object::addEvent(std::string event){
    events.push_back(event);
    eventCount++;
}


void Object::removeEvent(std::string event){
    for(int i = 0; i < eventCount; i++){
        if (events[i] == event){
            events.erase(events.begin() + i);
            eventCount--;
        }
    }
}

bool Object::hasEvent(std::string event){
    for(int i = 0; i < eventCount; i++){
        if (events[i] == event){
            return true;
        }
    }
    return false;
}

void Object::clearEvents(){
    events.clear();
    eventCount = 0;
}

int Object::getEventCount(){
    return eventCount;
}

std::vector <std::string> Object::getEvents(){
    return events;
}

void Object::handleEvent(Event* event){
    //user defined
}

int Object::getDespawnCount(){
    return despawnCount;
}

int Object::getTimeToDespawn(){
    return timeToDespawn;
}

void Object::setDespawnCount(int despawnCount){
    this->despawnCount = despawnCount;
}

void Object::setTimeToDespawn(int timeToDespawn){
    this->timeToDespawn = timeToDespawn;
}
