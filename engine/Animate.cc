#include "Animate.h"
#include <iostream>

Animate::Animate(): shape{0}, currFrame{}, frameIndex{0}, frameDelayCount{0}, boundary() {}

Shape *Animate::getShape(){
    return shape;
}

Hitbox Animate::getBoundary(){
    return boundary;
}

int Animate::getFrameIndex(){
    return frameIndex;
}

int Animate::getFrameDelayCount(){
    return frameDelayCount;
}

std::string Animate::getLabel(){
    return label;
}

void Animate::setShape(Shape *newShape){
    shape = newShape;
    frameIndex = 0;
    if (shape){
        Hitbox newBoundary = Hitbox(Position(0, 0), shape->getWidth(), shape->getLength());
        boundary = newBoundary;
    } 
    else{
        boundary = Hitbox();
    }
}

void Animate::setBoundary(Hitbox newBoundary){
    boundary = newBoundary;
}

void Animate::setFrameIndex(int newFrameIndex){
    frameIndex = newFrameIndex;
}

void Animate::setFrameDelayCount(int newFrameDelayCount){
    frameDelayCount = newFrameDelayCount;
}

void Animate::setLabel(std::string newLabel){
    label = newLabel;
}

void Animate::update(){
    if (shape){
        if (frameDelayCount < shape->getFrameDelay()){
            frameDelayCount++;
        }else{
            frameDelayCount = 0;
            frameIndex = (frameIndex + 1) % shape->getFrameCount();
            currFrame = shape->getFrame(frameIndex);
        }
    }
}

Frame Animate::getCurrFrame(){
    return currFrame;
}

