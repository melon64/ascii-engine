#include "EventManager.h"

EventManager::EventManager(){
  size = 0;
}

EventManager::~EventManager(){
  clear();
}

void EventManager::addEvent(Event *e){
  events.push_back(e);
  size++;
}

void EventManager::removeEvent(Event *e){
  for(int i = 0; i < size; i++){
    if(events[i] == e){
      removeEvent(i);
      break;
    }
  }
}

void EventManager::removeEvent(int index){
  delete events[index];
  events.erase(events.begin() + index);
  size--;
}

Event *EventManager::getEvent(int index){
  return events[index];
}

int EventManager::getSize(){
  return size;
}

void EventManager::clear(){
  for(int i = 0; i < size; i++){
    delete events[i];
  }
  events.clear();
  size = 0;
}

Event *EventManager::operator[](int index){
  return events[index];
}

