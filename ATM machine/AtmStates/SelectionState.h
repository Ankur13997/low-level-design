#pragma once
#include "States.h"
class SelectionState: public States
{
private:
    /* data */
public:
    SelectionState(){
         cout<<"ATM is in Selection State"<<endl;
    }
    ~SelectionState(){}
    void  showState() override;
    
    void exit(shared_ptr<Atm> atm)override;
    
    void returnCard()override;
    void selectOperation(shared_ptr<Atm> atm, shared_ptr<Card> card,TransactionType txnType)override;
    
};
