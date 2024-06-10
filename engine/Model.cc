#include "Model.h"

void Model::addView(View* view){
    this->view = view;
}

void Model::addController(Controller* controller){
    this->controller = controller;
}

void Model::notifyView(ObjectManager *objects, std::string *statuses){
    this->view->notify(objects, statuses);
}

Action Model::getAction(){
    return this->controller->getAction();
}

bool Model::hasView(){
    return this->view != nullptr;
}

bool Model::hasController(){
    return this->controller != nullptr;
}


