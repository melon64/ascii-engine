#include "Hitbox.h"

Hitbox::Hitbox(){
  position = Position();
  length = 0;
  width = 0;
}

Hitbox::Hitbox(Position position, int length, int width){
  this->position = position;
  this->length = length;
  this->width = width;
}

bool Hitbox::operator==(const Hitbox& hitbox){
  return position == hitbox.position && length == hitbox.length && width == hitbox.width;
}

Position Hitbox::getPosition(){
  return position;
}

int Hitbox::getLength(){
  return length;
}

int Hitbox::getWidth(){
  return width;
}

void Hitbox::setPosition(Position position){
  this->position = position;
}

void Hitbox::setLength(int length){
  this->length = length;
}

void Hitbox::setWidth(int width){
  this->width = width;
}

bool Hitbox::isColliding(Hitbox h) {
    Position otherPos = h.getPosition();
    int otherLength = h.getLength();
    int otherWidth = h.getWidth();

    Position thisPos = this->getPosition();
    int thisLength = this->getLength();
    int thisWidth = this->getWidth();

    if (thisPos.getX() + thisWidth <= otherPos.getX() || otherPos.getX() + otherWidth <= thisPos.getX()) {
        return false;
    }

    if (thisPos.getY() + thisLength <= otherPos.getY() || otherPos.getY() + otherLength <= thisPos.getY()) {
        return false;
    }

    return true;
}
