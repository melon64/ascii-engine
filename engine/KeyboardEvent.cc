#include "KeyboardEvent.h"
#include <string>

KeyboardEvent::KeyboardEvent(){
    setType("KeyboardEvent");
    key = 0;
}

KeyboardEvent::KeyboardEvent(int key){
    this->key = key;
}

int KeyboardEvent::getKey(){
    return key;
}

void KeyboardEvent::setKey(int key){
    this->key = key;
}


