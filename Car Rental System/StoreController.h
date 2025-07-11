#pragma once
#include "Store.h"
#include<unordered_map>
#include<memory>
using namespace std;

class StoreController
{
private:
    /* data */
    unordered_map<City,vector<shared_ptr<Store>>>cityVsStore;
    vector<shared_ptr<Store>>allStores;
public:
    StoreController(/* args */);

    void addStore(City city,shared_ptr<Store>store);

    vector<shared_ptr<Store>>getStoreByCity(City city);
    ~StoreController();
};


