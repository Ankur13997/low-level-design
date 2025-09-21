#include "VendingMachine.h"
#include "VendingStates/Impl/IdleState.h"
VendingMachine::VendingMachine(/* args */)
{
    inventory= make_shared<Inventory>();
    state=make_shared<IdleState>();
    coinList=vector<Coin>();
}

VendingMachine::~VendingMachine()
{
}

shared_ptr<Inventory> VendingMachine::getInventory(){return inventory;}
shared_ptr<States> VendingMachine::getState(){return state;}
vector<Coin> VendingMachine::getCoinList(){return coinList;}
void VendingMachine::setState(shared_ptr<States> newState)
{
    state=newState;
}
void VendingMachine::addCoin(Coin coin)
{
    coinList.push_back(coin);
}

void VendingMachine::setCoinList(vector<Coin>coinLists)
{
  
    coinList=coinLists;
   
}