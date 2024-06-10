#include "Event.h"
#include "Object.h"

class CollisionEvent : public Event {
    Position position;
    Object *objectCollider;
    Object *objectCollided;
    
  public:
    CollisionEvent();
    CollisionEvent(Object *o1, Object *o2, Position p);
    ~CollisionEvent();
    Position getPosition();
    Object *getObjectCollider();
    Object *getObjectCollided();
    void setPosition(Position p);
    void setObjectCollider(Object *o);
    void setObjectCollided(Object *o);

};
