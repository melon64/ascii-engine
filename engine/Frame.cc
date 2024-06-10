#include <string>
#include "Frame.h"
#include "Position.h"

Frame::Frame(){
  length = 0;
  width = 0;
  word = "";
}

Frame::Frame(int length, int width, std::string word){
  this->length = length;
  this->width = width;
  this->word = word;
}

void Frame::operator=(const Frame &frame){
  length = frame.length;
  width = frame.width;
  word = frame.word;
}

int Frame::getLength(){
  return length;
}

int Frame::getWidth(){
  return width;
}

std::string Frame::getWord(){
  return word;
}

void Frame::setLength(int length){
  this->length = length;
}

void Frame::setWidth(int width){
  this->width = width;
}

void Frame::setWord(std::string word){
  this->word = word;
}

