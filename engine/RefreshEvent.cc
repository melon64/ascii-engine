#include "RefreshEvent.h"

RefreshEvent::RefreshEvent(){
    setType("RefreshEvent");
    setRefreshes(0);
}

RefreshEvent::~RefreshEvent(){
}

int RefreshEvent::getRefreshes(){
    return refreshes;
}

void RefreshEvent::setRefreshes(int refreshes){
    this->refreshes = refreshes;
}

