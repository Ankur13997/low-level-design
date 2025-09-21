#include "HasMoneyState.h"
#include<iostream>
#include "../../VendingMachine.h"
#include "SelectionState.h"
#include "IdleState.h"
using namespace std;

HasMoneyState::HasMoneyState(/* args */)
{
    cout<<"Vending Machine is in HasMoney State"<<endl;
}

HasMoneyState::~HasMoneyState()
{
}

void HasMoneyState::showState()
{
    cout<<"HasMoneyState"<<endl;
}
void HasMoneyState::clickOnStartProductSelectionButton(shared_ptr<VendingMachine>machine)
{
    cout<<"Product Selection Button is pressed"<<endl;
    machine->setState(make_shared<SelectionState>());
    machine->getState()->showState();
}

void HasMoneyState::insertCoin(shared_ptr<VendingMachine>machine,Coin coin)
{
    cout<<"Coin added successfully"<<endl;
    machine->addCoin(coin);
}

vector<Coin> HasMoneyState::refundFullMoney(shared_ptr<VendingMachine>machine)
{
    cout<<"Full refund money initiated"<<endl;
    auto coinList=machine->getCoinList();
    machine->setState(make_shared<IdleState>(machine));
    machine->getState()->showState();
    return coinList;
}