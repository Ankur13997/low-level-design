#include "CashWithDraw.h"
#include "../Atm.h"
#include "../Card.h"
#include "States.h"
#include "IdleState.h"
#include "SelectionState.h"

void CashWithDraw::cashWithdrawal(shared_ptr<Atm> atm, shared_ptr<Card> card,int withdrawAmount)
{
    int atmBalance= atm->getAmount();
    int accountBalnce = card->getBankAccount()->getBalance();
    if(atmBalance < withdrawAmount )
    {
        cout<<"Insufficient Balance in the ATM"<<endl;
        exit(atm);
        return ;
    }

    if(accountBalnce < withdrawAmount)
    {
        cout<<"Insufficient Balance in your account"<<endl;
        exit(atm);
        return ;
    }

    atm->updateAmount(atmBalance - withdrawAmount );
    card->getBankAccount()->updateAmount(accountBalnce - withdrawAmount);
    cout<<"Please Collect your cash"<<endl;
    cout<<"Your remaining amount: "<<accountBalnce - withdrawAmount<<endl;
    atm->setState(make_shared<SelectionState>());

}
void  CashWithDraw::showState() 
{
    cout<<"CashWithDraw State"<<endl;
}
void CashWithDraw::returnCard() 
{
    cout<<"Please collect your card"<<endl;
}
void CashWithDraw::exit(shared_ptr<Atm> atm) 
{
    returnCard();
    atm->setState(make_shared<IdleState>());
    cout<<"Exit happens"<<endl;
}