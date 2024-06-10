#ifndef OBJECT_H
#define OBJECT_H

#include "Animate.h"
#include "Hitbox.h"
#include "Position.h"
#include "Frame.h"
#include <string>
#include <vector>

class Event;

enum Solidity {
    SOLID, //cannot pass through
    SOFT, //can pass through, still collision
    FOG //can pass through, no collision
};

class Object {
    int id; //allocated by engine
    std::string type; //user defined name of object
    Position position, prevPosition;
    Hitbox hitbox;
    Animate animation;
    std::string resourceName; //name of resource to load

    //direction and speed of movement
    Position direction;
    int velocity, velocityDelay, velocityCount;

    int height; //height on plane
    Solidity solidity; //solidity of object
    std::vector <std::string> events; //events to handle
    int eventCount; //number of events

    //despawn semantics
    int despawnCount, timeToDespawn;

  public:
    Object(); 
    virtual ~Object();
    int getId();
    std::string getType();
    Position getPosition();
    Hitbox getHitbox();
    Animate getAnimation();
    std::string getResourceName();
    Position getDirection();
    int getVelocity();
    int getVelocityDelay();
    int getHeight();
    Solidity getSolidity();
    Position getPrevPosition();
    int getDespawnCount();
    int getTimeToDespawn();

    void setId(int);
    void setType(std::string);
    void setPosition(Position);
    void setHitbox(Hitbox);
    void setAnimation(Animate);
    void setResourceName(std::string);
    void setDirection(Position);
    void setVelocity(int);
    void setVelocityDelay(int);
    void setHeight(int);
    void setSolidity(Solidity);
    void setPrevPosition(Position);
    void setStaticPosition(Position);
    void setDespawnCount(int);
    void setTimeToDespawn(int);

    void addEvent(std::string); //add an event to the list
    void removeEvent(std::string); //remove an event from the list
    bool hasEvent(std::string); //check if an event is in the list
    void clearEvents(); //clear the list of events
    int getEventCount(); //get the number of events in the list
    std::vector <std::string> getEvents(); //get the list of events

    void setShape(std::string resource); //get the resource and set the shape
    Position update(); //update position based on direction and velocity, check for collision
    virtual void handleEvent(Event* event);

};

#endif
