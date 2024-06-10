#include "State.h"

State::State(){ started = false; }

State::~State(){}

std::string State::getType(){
  return type;
}

bool State::isStarted(){
  return started;
}

void State::setStarted(bool b){
  started = b;
}

bool State::start(){ return started; }

void State::end(){}

void State::setType(std::string newType){
  type = newType;
}

