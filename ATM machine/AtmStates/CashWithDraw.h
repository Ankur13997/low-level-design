#pragma once
#include "States.h"

class CashWithDraw :public States
{
private:
    /* data */
public:
    CashWithDraw(/* args */){
        cout<<"ATM is in CashWithDraw State"<<endl;
    }
    ~CashWithDraw(){}
    void cashWithdrawal(shared_ptr<Atm> atm, shared_ptr<Card> card,int withdrawAmount)override;

    void  showState() override;
    
    void exit(shared_ptr<Atm> atm)override;
    
    void returnCard()override;
};

