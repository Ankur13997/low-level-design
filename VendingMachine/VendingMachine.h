#pragma once
#include "Inventory.h"
// #include "VendingStates/States.h"
#include "Coins.h"

class States;
class VendingMachine
{
private:
    /* data */
    shared_ptr<Inventory>inventory;
    shared_ptr<States>state;
    vector<Coin>coinList;

public:
    VendingMachine(/* args */);
    ~VendingMachine();
    shared_ptr<Inventory> getInventory();
    shared_ptr<States> getState();
    vector<Coin> getCoinList();
    void setState(shared_ptr<States> newState);
    void addCoin(Coin coin);
    void setCoinList(vector<Coin>coinList);

};

