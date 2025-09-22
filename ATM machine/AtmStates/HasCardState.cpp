#include "HasCardState.h"
#include "../Atm.h"
#include "../Card.h"
#include "States.h"
#include "SelectionState.h"
#include "IdleState.h"

void HasCardState::authenticatePin(shared_ptr<Atm> atm, shared_ptr<Card> card,int pinCode) 
{
    bool isValid = card->validate(pinCode);
    if(isValid)
    {
        cout<<"PinCode Validated"<<endl;
        atm->setState(make_shared<SelectionState>());
    }
    else
    {
        cout<<"Invalid Pincode"<<endl;
        exit(atm);
    }
}
void  HasCardState::showState() 
{
    cout<<"HasCardState State"<<endl;
} 

void HasCardState::returnCard() 
{
    cout<<"Please collect your card"<<endl;
}
void HasCardState::exit(shared_ptr<Atm> atm) 
{
    returnCard();
    atm->setState(make_shared<IdleState>());
    cout<<"Exit happens"<<endl;
}