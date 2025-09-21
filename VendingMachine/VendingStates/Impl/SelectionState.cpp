#include "SelectionState.h"
#include "../../VendingMachine.h"
#include "DispenseState.h"
#include "IdleState.h"

SelectionState::SelectionState(/* args */)
{
    cout<<"Currently Vending Machine is in Selection State"<<endl;
}

SelectionState::~SelectionState()
{
}
void SelectionState::showState()
{
    cout<<"SelectionState"<<endl;
}
void SelectionState::chooseProduct(shared_ptr<VendingMachine>machine,int codeNumber)
{

    auto itemShelf= machine->getInventory()->getItemByCode(codeNumber);
    if(itemShelf==nullptr)
    {
        cout<<"Please Enter Correct Code"<<endl;
        SelectionState::refundFullMoney(machine);
        return ;
    }
    // paid by user
    int paidByUser=0;
    for(auto coin : machine->getCoinList())
    {
        paidByUser+= getValue(coin);
    }
    
    if(paidByUser < itemShelf->getItem().getCost())
    {
        cout<<"Insufficient Balance, moving to Idle State"<<endl;
        SelectionState::refundFullMoney(machine);
    }
    else
    {
        if(paidByUser > itemShelf->getItem().getCost())
        {
            int change=paidByUser-itemShelf->getItem().getCost();
            SelectionState::getChange(change);

        }
        machine->setState(make_shared<DispenseState>(machine,codeNumber));
        cout<<"Test"<<endl;
        machine->getState()->showState();
        cout<<"Test"<<endl;
    }

}

int SelectionState::getChange(int remainingMoney)
{
    cout<<"Return the change in the Coin Dispense tray "<<remainingMoney<<endl;
    return remainingMoney;
}

vector<Coin> SelectionState::refundFullMoney(shared_ptr<VendingMachine>machine)
{
    cout<<"Full refund money initiated"<<endl;
    auto coinList=machine->getCoinList();
    machine->setState(make_shared<IdleState>(machine));
    machine->getState()->showState();
    return coinList;
}
