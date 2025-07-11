#include "CarRentalSystem.h"

CarRentalSystem::CarRentalSystem(/* args */){
    storeController=make_shared<StoreController>();
}

CarRentalSystem::~CarRentalSystem(){}

void CarRentalSystem::addstore(City city,shared_ptr<Store>store)
{
    storeController->addStore(city,store);
}