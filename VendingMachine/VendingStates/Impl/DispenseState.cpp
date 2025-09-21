#include "DispenseState.h"
#include "../../VendingMachine.h"
#include "IdleState.h"
#include<iostream>
using namespace std;
DispenseState::DispenseState(/* args */shared_ptr<VendingMachine>machine,int codeNumber)
{
    cout<<"Currently Vending Machine is in Dispense State"<<endl;
   // DispenseState::dispenseProduct(machine,codeNumber);

}

DispenseState::~DispenseState()
{
}
void DispenseState::showState()
{
    cout<<"DispenseState"<<endl;
}
Item DispenseState::dispenseProduct(shared_ptr<VendingMachine>machine,int codeNumber)
{
    cout<<"Item has been dispensed"<<endl;
    auto item=machine->getInventory()->getItemByCode(codeNumber);
    item->setStatus();
    machine->setState(make_shared<IdleState>(machine));
    machine->getState()->showState();
    return item->getItem();
    
}

