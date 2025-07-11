#pragma once
#include "User.h"
#include "StoreController.h"

using namespace std;

class CarRentalSystem
{
private:
    /* data */
    
public:
    vector<shared_ptr<User>>allUser;
    shared_ptr<StoreController> storeController;
    CarRentalSystem(/* args */);

    ~CarRentalSystem();
    void addstore(City city,shared_ptr<Store>store);

    
};
