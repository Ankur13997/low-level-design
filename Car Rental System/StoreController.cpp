#include "StoreController.h"

StoreController::StoreController(){}

void StoreController::addStore(City city,shared_ptr<Store>store)
{
    cityVsStore[city].push_back(store);
    allStores.push_back(store);
}

vector<shared_ptr<Store>>StoreController::getStoreByCity(City city)
{
    if(cityVsStore.count(city))
        return cityVsStore[city];
    return {};
}
StoreController::~StoreController(){}