#include "Position.h"

Position::Position(){
  x = 0;
  y = 0;
}

Position::Position(int x, int y){
  this->x = x;
  this->y = y;
}

int Position::getX(){
  return x;
}

int Position::getY(){
  return y;
}

void Position::setX(int x){
  this->x = x;
}

void Position::setY(int y){
  this->y = y;
}

bool Position::operator==(const Position& position){
  return x == position.x && y == position.y;
}
