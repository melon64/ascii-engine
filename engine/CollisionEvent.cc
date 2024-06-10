#include "CollisionEvent.h"

CollisionEvent::CollisionEvent(){
  setType("CollisionEvent");
  position = Position();
  objectCollider = nullptr;
  objectCollided = nullptr;
}

CollisionEvent::CollisionEvent(Object *o1, Object *o2, Position p){
  setType("CollisionEvent");
  position = p;
  objectCollider = o1;
  objectCollided = o2;

}

CollisionEvent::~CollisionEvent(){}

Position CollisionEvent::getPosition(){
  return position;
}

Object *CollisionEvent::getObjectCollider(){
  return objectCollider;
}

Object *CollisionEvent::getObjectCollided(){
  return objectCollided;
}

void CollisionEvent::setPosition(Position p){
  position = p;
}

void CollisionEvent::setObjectCollider(Object *o){
  objectCollider = o;
}

void CollisionEvent::setObjectCollided(Object *o){
  objectCollided = o;
}

