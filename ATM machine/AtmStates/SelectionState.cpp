#include "SelectionState.h"
#include "../Atm.h"
#include "../Card.h"
#include "States.h"
#include "IdleState.h"
#include "CashWithDraw.h"
#include "DisplayAmount.h"
void  SelectionState::showState() 
{
    cout<<"Selection State"<<endl;
} 

void SelectionState::returnCard() 
{
    cout<<"Please collect your card"<<endl;
}
void SelectionState::exit(shared_ptr<Atm> atm) 
{
    returnCard();
    atm->setState(make_shared<IdleState>());
    cout<<"Exit happens"<<endl;
}

void SelectionState::selectOperation(shared_ptr<Atm> atm, shared_ptr<Card> card,TransactionType txnType) 
{
    switch (txnType)
    {
    case CASHWITHDRAW:
        atm->setState(make_shared<CashWithDraw>());
        break;
    case DISPLAYAMOUNT:
        atm->setState(make_shared<DisplayAmount>());
        break;
    default:
        break;
    }
}