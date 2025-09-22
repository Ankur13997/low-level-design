#include "../Atm.h"
#include "../Card.h"
#include "States.h"
#include "IdleState.h"
#include "DisplayAmount.h"
#include "SelectionState.h"
void DisplayAmount::displayBalance(shared_ptr<Atm> atm, shared_ptr<Card> card)  
{
    cout<<"Your Balance is: "<<card->getBankAccount()->getBalance()<<endl;
    atm->setState(make_shared<SelectionState>());
}

void  DisplayAmount::showState() 
{
    cout<<"DisplayAmount State"<<endl;
}
void DisplayAmount::returnCard() 
{
    cout<<"Please collect your card"<<endl;
}
void DisplayAmount::exit(shared_ptr<Atm> atm) 
{
    returnCard();
    atm->setState(make_shared<IdleState>());
    cout<<"Exit happens"<<endl;
}