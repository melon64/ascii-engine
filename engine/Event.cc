#include "Event.h"

Event::Event(){}

Event::~Event(){}

void Event::setType(std::string type){
  this->type = type;
}

std::string Event::getType(){
  return type;
}
