#include "MouseEvent.h"
#include "Position.h"

MouseEvent::MouseEvent(){
    setType("MouseEvent");
    position = Position();
    button = LEFT;
}

MouseEvent::MouseEvent(Position position, Button button){
    this->position = position;
    this->button = button;
}

Position MouseEvent::getPosition(){
    return position;
}

Button MouseEvent::getButton(){
    return button;
}

void MouseEvent::setPosition(Position position){
    this->position = position;
}

void MouseEvent::setButton(Button button){
    this->button = button;
}
