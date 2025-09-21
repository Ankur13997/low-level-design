#include "IdleState.h"
#include "../../VendingMachine.h"
#include "HasMoneyState.h"
#include<iostream>
using namespace std;
IdleState::IdleState(/* args */)
{
    cout<<"Currently Vending Machine is in Idle State"<<endl;
}

IdleState::IdleState(/* args */shared_ptr<VendingMachine>machine)
{
    cout<<"Currently Vending Machine is in Idle State"<<endl;
   
    machine->setCoinList({});
}

IdleState::~IdleState()
{
}

void IdleState::showState()
{
    cout<<"IdleState"<<endl;
}
void IdleState::clickOnInsertCoinButton(shared_ptr<VendingMachine>machine)
{
    cout<<"Insert Coin Button is pressed"<<endl;
    machine->setState(make_shared<HasMoneyState>());
    machine->getState()->showState();
}