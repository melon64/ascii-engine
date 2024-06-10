#include "ObjectManager.h"

ObjectManager::ObjectManager(){
  size = 0;
}

ObjectManager::~ObjectManager(){
  clear();
}

void ObjectManager::addObject(Object *o){
  objects.push_back(o);
  size++;
}

void ObjectManager::removeObject(Object *o){
  for(int i = 0; i < size; i++){
    if(objects[i] == o){
      removeObject(i);
      break;
    }
  }
}

void ObjectManager::removeObject(int index){
  objects.erase(objects.begin() + index);
  size--;
}

Object *ObjectManager::getObject(int index){
  return objects[index];
}

int ObjectManager::getSize(){
  return size;
}

void ObjectManager::clear(){
  for(int i = 0; i < size; i++){
    delete objects[i];
  }
  objects.clear();
  size = 0;
}

Object *ObjectManager::operator[](int index){
  return objects[index];
}


