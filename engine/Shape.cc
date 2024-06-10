#include "Shape.h"
#include <iostream>

Shape::Shape(int maxFrameCount): maxFrameCount{maxFrameCount}, frameCount{0}, width{0}, length{0}, frameDelay{0}, frames(new Frame[maxFrameCount]), label{}{
    //add error checking
}

Shape::~Shape(){
    if (frames){
        delete[] frames;
    }
}

int Shape::getLength(){
    return length;
}

int Shape::getWidth(){
    return width;
}

int Shape::getFrameCount(){
    return frameCount;
}

int Shape::getMaxFrameCount(){
    return maxFrameCount;
}

int Shape::getFrameDelay(){
    return frameDelay;
}

Frame Shape::getFrame(int index){
    return frames[index];
}

std::string Shape::getLabel(){
    return label;
}

void Shape::setLength(int length){
    this->length = length;
}

void Shape::setWidth(int width){
    this->width = width;
}

void Shape::setFrameDelay(int frameDelay){
    this->frameDelay = frameDelay;
}

void Shape::addFrame(Frame frame){
    if (frameCount < maxFrameCount){
        frames[frameCount] = frame;
        frameCount++;
    }
}

void Shape::setLabel(std::string label){
    this->label = label;
}

